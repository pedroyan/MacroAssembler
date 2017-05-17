#include "Assembler.h"
#include "ErrorPrinter.h"
#include "StringLibrary.h"
#include <regex>

using std::regex;
using std::regex_match;

Assembler::Assembler(string outFileName) : scanner(outFileName,this), generator(outFileName){
	positionCount = 0;
	lineCount = 1;
	successAssemble = true;
	sectionFlags = 0;
	beginFlags = 0;
	hasStop = false;
}

Assembler::~Assembler() {
}

int Assembler::GetLine() {
	return lineCount;
}

int Assembler::ExecuteDirective(string directiveName, DirectiveInfo const * info, vector<string> operands, SymbolInfo* symbol) {
	int positionSkip = 0;
	int opsize = operands.size();

	if ((info->operandCount != -1 && info->operandCount != opsize) || (info->operandCount == -1 && opsize != 0 && opsize != 1)) {
		ShowError("Diretiva invalida: Quantidade de operandos errada.",Syntatic);
		return 0;
	}

	if (directiveName  == "section") {
		positionSkip = ExecuteSection(operands);
	} else if (directiveName == "space") {
		if (symbol == nullptr) {
			ShowError("Nenhum rotulo definido para a diretiva space", Syntatic);
			return 0;
		}

		if (opsize == 0) {
			positionSkip = 1;
		} else {
			auto argument = operands[0];
			int toReturn;

			if (TryStringToInt(argument, &toReturn)) {
				symbol->spaceCount = toReturn;
				return toReturn;
			} else {
				ShowError("Operando Invalido:" + argument, Syntatic);
			}
		}
	} else if (directiveName == "extern") {
		// Modifica o rotulo passado na tabela de simbolos com o valor 0
		// e com a flag externa setada
		if (symbol == nullptr) {
			ShowError("Nenhum rótulo foi definido para a diretiva Extern",Syntatic);
			return 0;
		}
		symbol->address = 0;
		symbol->externo = true;
	} else if (directiveName == "public") {
		//insere o operando na tabela de definicoes
		TableManager::InsertDefinition(operands[0]);
	} else if (directiveName == "begin") {
		if (beginFlags & Begin) {
			ShowError("Siretiva begin redefinida", Semantic);
			return 0;
		}
		beginFlags = Begin;
	} else if (directiveName == "end") {
		if (!beginFlags & Begin) {
			ShowError("End não possui um Begin correspondente",Semantic);
			return 0;
		}

		if (beginFlags & BeginFlags::End) {
			ShowError("Diretiva end redefinida", Semantic);
			return 0;
		}

		beginFlags = beginFlags | BeginFlags::End;

	} else if (directiveName == "const") {
		if (symbol == nullptr) {
			ShowError("Nenhum rótulo foi definido para a diretiva Const", Syntatic);
			return 0;
		}

		int constval;
		if (!TryStringToInt(operands[0],&constval)) {
			ShowError("Nao foi possivel converter " + operands[0] + " para um numero", Semantic);
			return 0;
		}

		symbol->isConst = true;
		symbol->constValue = constval;
	} else {
		positionSkip = info->size;
	}
	return positionSkip;
}

void Assembler::Assemble() {
	firstPass();

	scanner.RestartStream();
	scanner.SuppressErrors = true;

	secondPass();
	generateObjectFile();
}

void Assembler::firstPass() {
	while (scanner.CanRead()) {
		auto dto = scanner.GetNextTokens();
		if (dto.Operacao=="") {
			if (!dto.isEmpty) {
				successAssemble = false;
			}
			lineCount++;
			continue;
		}

		if (dto.Operacao=="if") {
			ShowError("Diretiva IF nao preprocessada", Semantic);
		}
		
		SymbolInfo* symbolCreated = nullptr;
		if (dto.Rotulo != "") {
			auto symbol = TableManager::GetSymbol(dto.Rotulo);
			if (symbol != nullptr) {
				ShowError("Simbolo " + dto.Rotulo + "redefinido", ErrorType::Semantic);
			} else {
				symbolCreated = TableManager::InsertSymbol(dto.Rotulo, SymbolInfo(positionCount, false));
			}
		}

		auto instruction = TableManager::GetInstruction(dto.Operacao);
		if (instruction != nullptr) {
			positionCount += instruction->operandCount + 1;
			if (dto.Operacao == "stop") {
				hasStop = true;
			}
		} else {
			auto directive = TableManager::GetDirective(dto.Operacao);
			if (directive != nullptr) {
				positionCount += ExecuteDirective(dto.Operacao, directive,dto.Operandos, symbolCreated);
			} else {
				ShowError("Operacao " + dto.Operacao + " nao identificada", ErrorType::Syntatic);
			}
		}
		lineCount++;
	}

	setDefinitionTableValues();
	FirstPassLastChecks();
	TableManager::Diagnostic_PrintSymbols();
	TableManager::Diagnostic_PrintDefinitions();
}

void Assembler::secondPass() {
	positionCount = 0;
	lineCount = 1;

	while (scanner.CanRead()) {
		auto dto = scanner.GetNextTokens();
		if (dto.Operacao=="" || (dto.Operacao != "section" && !CheckLabels(dto.Operandos))) {
			continue;
		}

		auto instruction = TableManager::GetInstruction(dto.Operacao);
		if (instruction != nullptr) {
			//positionCount += instruction->operandCount + 1;
			ValidateAndWriteInstruction(instruction, dto.Operandos);
		} else {
			auto directive = TableManager::GetDirective(dto.Operacao);
			if (directive == nullptr) {
				ShowError("Operacao " + dto.Operacao + " nao identificada", Syntatic);
			}
			if (dto.Operacao == "space") {
				auto symbol = TableManager::GetSymbol(dto.Rotulo);
				generator.WriteDirective(WrittenDirectivesType::SPACE, symbol->spaceCount);
			} else if (dto.Operacao=="const") {
				int result;
				if (TryStringToInt(dto.Operandos[0],&result)) {
					generator.WriteDirective(WrittenDirectivesType::CONST, result);
				} else {
					ShowError("Nao foi possivel converter valor passado para operador CONST para um inteiro", Semantic);
				}		
			}
		}
		
		lineCount++;
		//Para cada operando que é símbolo -> Procura operando na TS -> Se não achou:Erro, símbolo indefinido
	}
}

void Assembler::ShowError(string message, ErrorType type) {
	successAssemble = false;
	ErrorPrinter::ShowError(type, scanner.GetFileName(), lineCount, message);
}

int Assembler::ExecuteSection(vector<string> operands) {
	if (operands[0] == "text") {
		if (sectionFlags & Text) {
			ShowError("SECTION TEXT ja definida", ErrorType::Semantic);
			return 0;
		}
		sectionFlags = Text;
	} else if (operands[0] == "data") {

		if (sectionFlags & Data) {
			ShowError("SECTION DATA ja definida", ErrorType::Semantic);
			return 0;
		}

		if (!(sectionFlags & Text)) {
			ShowError("SECTION DATA definida antes de SECTION TEXT", ErrorType::Semantic);
			return 0;
		}

		sectionFlags = sectionFlags | Data;
	} else {
		ShowError("Diretiva Invalida: SECTION nao indentificada.", Syntatic);
	}
	return 0;
}

bool Assembler::TryStringToInt(string s, int* result) {
	if (StringLibrary::IsInteger(s)) {
		*result = std::stoi(s, nullptr);
		return true;
	} else if (StringLibrary::IsHexadecimal(s)) {
		*result = StringLibrary::ConvertHexaToInt(s);
		return true;
	} else {
		return false;
	}
}

void Assembler::FirstPassLastChecks() {
	if (!(sectionFlags & SectionFlags::Text)) {
		ShowError("Secao Text nao encontrada", Semantic);
	}

	bool isModule = (beginFlags & BeginFlags::Begin) && (beginFlags & BeginFlags::End);

	if ((beginFlags & BeginFlags::Begin) && !isModule) {
		ShowError("Diretiva END nao encontrada", Semantic);
	}

	if (!isModule && !hasStop) {
		ShowError("Instrucao STOP nao encontrada", Semantic);
	}
}

void Assembler::setDefinitionTableValues() {
	auto& table = TableManager::GetDefinitionTable();
	for (auto& it : table) {
		auto symbol = TableManager::GetSymbol(it.first);

		if (symbol != nullptr) {
			it.second = symbol->address;
		} else {
			ShowError("O simbolo publico " + it.first + " não foi definido", Semantic);
		}
	}
}

bool Assembler::CheckLabels(const vector<string>& operands) {

	bool success = true;
	for (auto& operando : operands) {

		auto plusOperands = StringLibrary::Tokenize(operando, "+");
		for (auto& plusOperand : plusOperands) {

			auto type = GetType(plusOperand);
			if (type == label) {
				auto symbol = TableManager::GetSymbol(plusOperand);
				if (symbol == nullptr) {
					ShowError("Simbolo indefinido: " + plusOperand, Syntatic);
					success = false;
				}
			}
		}
	}
	return success;
}

void Assembler::ValidateAndWriteInstruction(const InstructionInfo * info, const vector<string>& operands) {
	vector<string> operationSides;
	vector<ArgumentInfo> arguments;

	if (info->operandCount != operands.size()) {
		ShowError("Numero invalido de parametros para instrucao", Semantic);
		return;
	}

	if (info->opCode == OpCodes::DIV && !evaluateDiv(operands[0])) {
		return;
	}

	if (info->opCode == OpCodes::STORE || info->opCode == OpCodes::COPY || info->opCode == OpCodes::INPUT) {

		auto operand = info->opCode == OpCodes::COPY ? operands[1] : operands[0];

		auto symbol = TableManager::GetSymbol(operand);
		if (symbol == nullptr) {
			ShowError("Simbolo nao encontrado", Semantic);
			return;
		}
		if (symbol->isConst) {
			ShowError("Modificacao da constante " + operand, Syntatic);
			return;
		}
	}

	if (info->opCode >= OpCodes::JMP && info->opCode <= OpCodes::JMPZ) {
		// jump para lables invalidas
	}

	positionCount++; //Posicao da instrucao

	for (auto operand : operands) {
		auto checkedArgument = CalculateAndCheckArrayBoundaries(operand);
		if (checkedArgument.Extern) {
			TableManager::InsertUse(checkedArgument.SymbolName, positionCount);
		}
		arguments.push_back(checkedArgument);
		positionCount++;
	}

	generator.WriteInstruction((int)info->opCode, arguments);
}

bool Assembler::TryCalculateOperandRealValue(string operand, int & extractedValue, SymbolInfo** symbol, string& symbolName) {
	auto type = GetType(operand);

	int extractedNumber = 0;
	switch (type) {
		case Assembler::number:
			if (!TryStringToInt(operand, &extractedNumber)) {
				ShowError("argumento invalido fornecido para operacao +", Semantic);
				return false;
			}
			break;
		case Assembler::label:
			if ((*symbol) != nullptr) {
				ShowError("Nao e possivel utilizar simbolo " + operand +  " como indice de vetor.", Syntatic);
				return false;
			}

			*symbol = TableManager::GetSymbol(operand);
			if ((*symbol) == nullptr) {
				ShowError("Label " + operand + " nao encontrada", Semantic);
				return false;
			} else {
				extractedNumber = (*symbol)->address;
				symbolName = operand;
			}
			break;
	}
	extractedValue = extractedNumber;
	return true;
}

ArgumentInfo Assembler::CalculateAndCheckArrayBoundaries(const string& operand) {
	int sumResult = 0;
	ArgumentInfo toReturn(0,false);
	SymbolInfo* symbol = nullptr;
	string symbolName;

	auto operationSides = StringLibrary::Tokenize(operand, "+");

	for (auto plusOperand : operationSides) {
		int extractedValue;
		if (!TryCalculateOperandRealValue(plusOperand, extractedValue, &symbol, symbolName)) {
			return toReturn;
		}
		sumResult += extractedValue;
	}
	if (operationSides.size() > 1 && symbol == nullptr) {
		ShowError("uso de indices sem vetor", Syntatic);
		return toReturn;
	}

	if (symbol!=nullptr && symbol->spaceCount - 1 < sumResult - symbol->address && !symbol->externo) {
		ShowError("Uso de Endereco de memoria nao reservado em " + operand, Semantic);
		return toReturn;
	}

	//retorna também o symbolInfo para colocat na tabela de realocação
	toReturn.RealValue = sumResult;
	toReturn.Extern = symbol->externo;
	toReturn.SymbolName = symbolName;
	return toReturn;
}

Assembler::operandTypes Assembler::GetType(string operand) {
	regex numberRegex("[0-9]+");
	if (regex_match(operand,numberRegex) || StringLibrary::IsHexadecimal(operand)) {
		return operandTypes::number;
	}

	return operandTypes::label;
}

bool Assembler::evaluateDiv(const string & divOperand) {
	auto operandType = GetType(divOperand);
	switch (operandType) {
	case Assembler::number:
		int number;

		if (!TryStringToInt(divOperand, &number)) {
			ShowError("Nao foi possivel converter " + divOperand + " para um numero", Semantic);
			return false;
		}

		if (number == 0) {
			ShowError("Divisao por 0", Syntatic);
			return false;
		}
		break;
	case Assembler::label:
		auto symbol = TableManager::GetSymbol(divOperand);
		if (symbol == nullptr) {
			ShowError("Simbolo nao encontrado", Semantic);
			return false;
		}
		if (symbol->isConst && symbol->constValue == 0) {
			ShowError("Divisao por 0", Syntatic);
			return false;
		}
		break;
	}
	return true;
}

void Assembler::generateObjectFile() {
	if (!successAssemble) {
		printf("Existem erros de montagem presentes. Arquivo .o nao foi gerado");
		return;
	}

	if (beginFlags&BeginFlags::Begin) {
		generator.GenerateFile(GenerationType::Modular);
	} else {
		generator.GenerateFile(GenerationType::Direct);
	}
}

