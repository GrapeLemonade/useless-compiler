#include <bits/stdc++.h>
#define MAX_SRC_LEN 0x10000
namespace LexDefine {
	std::vector<std::string> TokenTypeName { // NOLINT(cert-err58-cpp)
			"Null",
			"IDENFR",   "INTCON",   "STRCON",       "MAINTK",   "CONSTTK",
			"INTTK",    "BREAKTK",  "CONTINUETK",   "IFTK",     "ELSETK",
			"NOT",      "AND",  	"OR",   		"WHILETK",  "GETINTTK",
			"PRINTFTK",	"RETURNTK",	"PLUS", 		"MINU",		"VOIDTK",
			"MULT",		"DIV",		"MOD",  		"LSS",		"LEQ",
			"GRE",		"GEQ",  	"EQL",  		"NEQ",		"ASSIGN",
			"SEMICN",	"COMMA",	"LPARENT",		"RPARENT",	"LBRACK",
			"RBRACK",	"LBRACE",	"RBRACE"
	};
	enum TokenType {
		NULLTK,
		IDENFR, INTCON, STRCON, MAINTK, CONSTTK,
		INTTK, BREAKTK, CONTINUETK, IFTK, ELSETK,
		NOT, AND, OR, WHILETK, GETINTTK,
		PRINTFTK, RETURNTK, PLUS, MINU, VOIDTK,
		MULT, DIV, MOD, LSS, LEQ,
		GRE, GEQ, EQL, NEQ, ASSIGN,
		SEMICN, COMMA, LPARENT, RPARENT, LBRACK,
		RBRACK, LBRACE, RBRACE
	};
	using Token = std::tuple<int, TokenType, std::string>;
	//                      Line    Type       Content
}
namespace GraDefine {
	using namespace LexDefine;
	enum GrammarType {
		CompUnit, Decl, ConstDecl, BType, ConstDef,
		ConstInitVal, VarDecl, VarDef, InitVal, FuncDef,
		MainFuncDef, FuncType, FuncFParams, FuncFParam, Block,
		BlockItem, Stmt, Exp, Cond, LVal,
		PrimaryExp, Number, UnaryExp, UnaryOp, FuncRParams,
		MulExp, AddExp, RelExp, EqExp, LAndExp,
		LOrExp, ConstExp, Lexeme, General
	};
	struct GrammarElement {
		std::string _name;
		GrammarType _type = General;
		std::vector<GrammarElement *> sub;
		GrammarElement() = default;
		~GrammarElement() = default;
	};
	struct GCompUnit : GrammarElement {
		GCompUnit () : GrammarElement() { _name = "CompUnit"; _type = CompUnit; }
	};
	struct GDecl : GrammarElement {
		GDecl () : GrammarElement() { _name = "Decl"; _type = Decl; }
	};
	struct GConstDecl : GrammarElement {
		GConstDecl () : GrammarElement() { _name = "ConstDecl"; _type = ConstDecl; }
	};
	struct GBType : GrammarElement {
		GBType () : GrammarElement() { _name = "BType"; _type = BType; }
	};
	struct GConstDef : GrammarElement {
		GConstDef () : GrammarElement() { _name = "ConstDef"; _type = ConstDef; }
	};
	struct GConstInitVal : GrammarElement {
		GConstInitVal () : GrammarElement() { _name = "ConstInitVal"; _type = ConstInitVal; }
	};
	struct GVarDecl : GrammarElement {
		GVarDecl () : GrammarElement() { _name = "VarDecl"; _type = VarDecl; }
	};
	struct GVarDef : GrammarElement {
		GVarDef () : GrammarElement() { _name = "VarDef"; _type = VarDef; }
	};
	struct GInitVal : GrammarElement {
		GInitVal () : GrammarElement() { _name = "InitVal"; _type = InitVal; }
	};
	struct GFuncDef : GrammarElement {
		GFuncDef () : GrammarElement() { _name = "FuncDef"; _type = FuncDef; }
	};
	struct GMainFuncDef : GrammarElement {
		GMainFuncDef () : GrammarElement() { _name = "MainFuncDef"; _type = MainFuncDef; }
	};
	struct GFuncType : GrammarElement {
		GFuncType () : GrammarElement() { _name = "FuncType"; _type = FuncType; }
	};
	struct GFuncFParams : GrammarElement {
		GFuncFParams () : GrammarElement() { _name = "FuncFParams"; _type = FuncFParams; }
	};
	struct GFuncFParam : GrammarElement {
		GFuncFParam () : GrammarElement() { _name = "FuncFParam"; _type = FuncFParam; }
	};
	struct GBlock : GrammarElement {
		GBlock () : GrammarElement() { _name = "Block"; _type = Block; }
	};
	struct GBlockItem : GrammarElement {
		GBlockItem () : GrammarElement() { _name = "BlockItem"; _type = BlockItem; }
	};
	struct GStmt : GrammarElement {
		GStmt () : GrammarElement() { _name = "Stmt"; _type = Stmt; }
	};
	struct GExp : GrammarElement {
		GExp () : GrammarElement() { _name = "Exp"; _type = Exp; }
	};
	struct GCond : GrammarElement {
		GCond () : GrammarElement() { _name = "Cond"; _type = Cond; }
	};
	struct GLVal : GrammarElement {
		GLVal () : GrammarElement() { _name = "LVal"; _type = LVal; }
	};
	struct GPrimaryExp : GrammarElement {
		GPrimaryExp () : GrammarElement() { _name = "PrimaryExp"; _type = PrimaryExp; }
	};
	struct GNumber : GrammarElement {
		GNumber () : GrammarElement() { _name = "Number"; _type = Number; }
	};
	struct GUnaryExp : GrammarElement {
		GUnaryExp () : GrammarElement() { _name = "UnaryExp"; _type = UnaryExp; }
	};
	struct GUnaryOp : GrammarElement {
		GUnaryOp () : GrammarElement() { _name = "UnaryOp"; _type = UnaryOp; }
	};
	struct GFuncRParams : GrammarElement {
		GFuncRParams () : GrammarElement() { _name = "FuncRParams"; _type = FuncRParams; }
	};
	struct GMulExp : GrammarElement {
		GMulExp () : GrammarElement() { _name = "MulExp"; _type = MulExp; }
	};
	struct GAddExp : GrammarElement {
		GAddExp () : GrammarElement() { _name = "AddExp"; _type = AddExp; }
	};
	struct GRelExp : GrammarElement {
		GRelExp () : GrammarElement() { _name = "RelExp"; _type = RelExp; }
	};
	struct GEqExp : GrammarElement {
		GEqExp () : GrammarElement() { _name = "EqExp"; _type = EqExp; }
	};
	struct GLAndExp : GrammarElement {
		GLAndExp () : GrammarElement() { _name = "LAndExp"; _type = LAndExp; }
	};
	struct GLOrExp : GrammarElement {
		GLOrExp () : GrammarElement() { _name = "LOrExp"; _type = LOrExp; }
	};
	struct GConstExp : GrammarElement {
		GConstExp () : GrammarElement() { _name = "ConstExp"; _type = ConstExp; }
	};
	struct GLexeme : GrammarElement {
		GLexeme () : GrammarElement() { _name = "Lexeme"; _type = Lexeme; }
		Token t;
		explicit GLexeme (const Token &tok) : GrammarElement() { _name = "Lexeme"; _type = Lexeme; t = tok; }
	};
}
namespace ErrDefine {
	using namespace std;
	vector< pair<int, char> > errors;
	int G_LastConsumedLineNo = -1;
	auto report = [] (int a, char b) { errors.emplace_back(a, b); };
	void panic(const string& s) {
		cerr << s << endl;
		exit(-2333);
	}
}
namespace SymDefine {
	using namespace std;
	enum Type {
		Void, Any, Int, IntArray, IntArrayArray // TODO: consider any type in handling
	};
	enum CV {
		Normal, Const //, Volatile, Restrict
	};
	struct Function {
		Type ret;
		string name;
		vector<Type> pars;
		bool operator < (const Function &o) const { // TODO: specify overloading
			if (name == o.name) {
				if (pars.size() != o.pars.size()) return pars.size() < o.pars.size();
				else {
					for (size_t i = 0; i < pars.size(); ++i) if (pars[i] != o.pars[i]) return pars[i] < o.pars[i];
					return false;
				}
			} else return name < o.name;
		}
	};
	struct Variable {
		Type type;
		CV cv;
		string name;
//		int dim1, dim2; not now = =
		bool operator < (const Variable &o) const { return name < o.name; }
	};
	struct Context {
		using ContextType = unsigned;
		ContextType _ = 0;
		static const ContextType inLoop = 0x0001;
		static const ContextType inIntFunc = 0x0002;
		static const ContextType inVoidFunc = 0x0004;
		bool has(ContextType q) const { return (_ & q); }
		Context operator | (ContextType t) {
			Context c = *this;
			c._ |= t;
			return c;
		}
	};
}
namespace Lex {
	using namespace std;
	using namespace LexDefine;
	char Src[MAX_SRC_LEN];
	vector<Token> tokens;
	int main(FILE *fIn) {
		int len = (int) fread(Src, 1, MAX_SRC_LEN, fIn);
		int line = 1;
		auto addToken = [&] (TokenType t, const string &s) { tokens.emplace_back(line, t, s); };
		for (char *p = Src; p < Src + len; ++p) {
			if (*p == '{') addToken(LBRACE, "{");
			else if (*p == '}') addToken(RBRACE, "}");
			else if (*p == '[') addToken(LBRACK, "[");
			else if (*p == ']') addToken(RBRACK, "]");
			else if (*p == '(') addToken(LPARENT, "(");
			else if (*p == ')') addToken(RPARENT, ")");
			else if (*p == ',') addToken(COMMA, ",");
			else if (*p == ';') addToken(SEMICN, ";");
			else if (*p == '%') addToken(MOD, "%");
			else if (*p == '*') addToken(MULT, "*");
			else if (*p == '+') addToken(PLUS, "+");
			else if (*p == '-') addToken(MINU, "-");
			else if (*p == '<') {
				if (p[1] == '=') addToken(LEQ, "<="), ++p;
				else addToken(LSS, "<");
			} else if (*p == '>') {
				if (p[1] == '=') addToken(GEQ, ">="), ++p;
				else addToken(GRE, ">");
			} else if (*p == '=') {
				if (p[1] == '=') addToken(EQL, "=="), ++p;
				else addToken(ASSIGN, "=");
			} else if (*p == '!') {
				if (p[1] == '=') addToken(NEQ, "!="), ++p;
				else addToken(NOT, "!");
			} else if (*p == '&') {
				if (p[1] == '&') addToken(AND, "&&"), ++p;
				else ErrDefine::panic("[L] no bitwise and support");
			} else if (*p == '|') {
				if (p[1] == '|') addToken(OR, "||"), ++p;
				else ErrDefine::panic("[L] no bitwise or support");
			} else if (*p == '/') {
				if (p[1] == '/') {
					while (p + 1 < Src + len && p[1] != '\n') ++p;
				}
				else if (p[1] == '*') {
					p += 2;
					while (p + 1 < Src + len && (p[0] != '*' || p[1] != '/')) ++p;
					if (p[0] != '*' || p[1] != '/') ErrDefine::panic("[L] block comment not ended");
					else ++p;
				}
				else addToken(DIV, "/");
			} else if (*p == '\"') {
				int t = 1;
				for (; p + t <= Src + len; ++t) {
					if (p[t] == 32 || p[t] == 33 || (40 <= p[t] && p[t] < 92) || (92 < p[t] && p[t] <= 126)) continue;
					else if ((35 <= p[t] && p[t] <= 39) || p[t] == 92) { { } continue; }
					else break;
//          disable L stage check for now
//					else if (p[t] == 92) {
//						if (p[t + 1] == 'n') ++t;
//						else break;
//					} else if (p[t] == '%') {
//						if (p[t + 1] == 'd') ++t;
//						else break;
//					} else break;
				}
				if (p[t] == '\"') addToken(STRCON, string(p, t + 1)), p += t;
				else ErrDefine::panic("[L] string literal not ended");
			} else if (isdigit(*p)) {
				int t = 1;
				for (; p + t <= Src + len; ++t) {
					if (!isdigit(p[t])) break;
				}
				if (*p != '0' || t == 1) addToken(INTCON, string(p, p + t)), p += (t - 1);
				else ErrDefine::panic("[L] no octal integer literal support");
			} else if (isalpha(*p) || *p == '_') {
				int t = 1;
				for (; p + t < Src + len; ++t) {
					if (isalpha(p[t]) || p[t] == '_' || isdigit(p[t])) continue;
					else break;
				}
				string s(p, t);
				if (s == "main") addToken(MAINTK, s);
				else if (s == "const") addToken(CONSTTK, s);
				else if (s == "int") addToken(INTTK, s);
				else if (s == "break") addToken(BREAKTK, s);
				else if (s == "continue") addToken(CONTINUETK, s);
				else if (s == "if") addToken(IFTK, s);
				else if (s == "else") addToken(ELSETK, s);
				else if (s == "while") addToken(WHILETK, s);
				else if (s == "getint") addToken(GETINTTK, s);
				else if (s == "printf") addToken(PRINTFTK, s);
				else if (s == "return") addToken(RETURNTK, s);
				else if (s == "void") addToken(VOIDTK, s);
				else addToken(IDENFR, s);
				p += (t - 1);
			} else if (isspace(*p)) {
				if (*p == '\n') ++line;
			}
			else ErrDefine::panic((string) "[L] stray char "
			                      + "0123456789abcdef"[(*p >> 4) & 15]
			                      + "0123456789abcdef"[*p & 15] + " in program");
//			printf("%c", *p);
		}
		return (int) tokens.size();
	}
}
namespace Gra {
	using namespace GraDefine;
	using namespace std;
	pair<bool, GCompUnit*> ParseCompUnit();
	pair<bool, GDecl*> ParseDecl();
	pair<bool, GConstDecl*> ParseConstDecl();
	pair<bool, GBType*> ParseBType();
	pair<bool, GConstDef*> ParseConstDef();
	pair<bool, GConstInitVal*> ParseConstInitVal();
	pair<bool, GVarDecl*> ParseVarDecl();
	pair<bool, GVarDef*> ParseVarDef();
	pair<bool, GInitVal*> ParseInitVal();
	pair<bool, GFuncDef*> ParseFuncDef();
	pair<bool, GMainFuncDef*> ParseMainFuncDef();
	pair<bool, GFuncType*> ParseFuncType();
	pair<bool, GFuncFParams*> ParseFuncFParams();
	pair<bool, GFuncFParam*> ParseFuncFParam();
	pair<bool, GBlock*> ParseBlock();
	pair<bool, GBlockItem*> ParseBlockItem();
	pair<bool, GStmt*> ParseStmt();
	pair<bool, GExp*> ParseExp();
	pair<bool, GCond*> ParseCond();
	pair<bool, GLVal*> ParseLVal();
	pair<bool, GPrimaryExp*> ParsePrimaryExp();
	pair<bool, GNumber*> ParseNumber();
	pair<bool, GUnaryExp*> ParseUnaryExp();
	pair<bool, GUnaryOp*> ParseUnaryOp();
	pair<bool, GFuncRParams*> ParseFuncRParams();
	pair<bool, GMulExp*> ParseMulExp();
	pair<bool, GAddExp*> ParseAddExp();
	pair<bool, GRelExp*> ParseRelExp();
	pair<bool, GEqExp*> ParseEqExp();
	pair<bool, GLAndExp*> ParseLAndExp();
	pair<bool, GLOrExp*> ParseLOrExp();
	pair<bool, GConstExp*> ParseConstExp();
	deque<Token> tokens; // NOLINT(cert-err58-cpp)
	GCompUnit *AST;
	inline TokenType fetchType(int i = 0) { return 0 <= i && i < (int) tokens.size() ? get<1>(tokens[i]) : NULLTK; }
	int main(vector<Token> v) {
		tokens = deque<Token>(v.begin(), v.end());
		const auto &res = ParseCompUnit();
		if (res.first) AST = res.second;
		else return -233333;
		return 0;
	}
	bool lAccept(GrammarElement *ret, const function<pair<bool, GrammarElement*>()> &Parser) {
		bool s;
		GrammarElement *g;
		tie(s, g) = Parser();
		if (s) ret->sub.emplace_back(g);
		return s;
	}
	bool lConsume(GrammarElement *ret, TokenType expected) {
		if (!tokens.empty() && get<1>(tokens.front()) == expected) {
			ret->sub.emplace_back(new GLexeme(tokens.front()));
			ErrDefine::G_LastConsumedLineNo = get<0>(tokens.front());
			tokens.pop_front();
			return true;
		} else {
			// due to lCon || lCon, this panic cannot be effective
//			ErrDefine::panic("expected token " + TokenTypeName[expected]);
			return false;
		}
	}
	bool lConsumeOrReport(GrammarElement *ret, int expected, char err) {
		if (!tokens.empty() && get<1>(tokens.front()) == expected) {
			ret->sub.emplace_back(new GLexeme(tokens.front()));
			tokens.pop_front();
			return true;
		} else {
			ErrDefine::report(ErrDefine::G_LastConsumedLineNo, err);
			return false;
		}
	}
	bool inline isKwToken(int t) {
		return t == CONSTTK || t == INTTK || t == BREAKTK || t == RETURNTK || t == VOIDTK
		       || t == CONTINUETK || t == IFTK || t == ELSETK || t == WHILETK || t == MAINTK;
	}
	bool inline isBrace(int t) {
		return t == LBRACE || t == RBRACE;
	}
	bool inline isFiExp(int t) {
		return t == IDENFR || t == NOT || t == PLUS || t == MINU || t == LPARENT || t == INTCON;
	}
	bool inline isBType(int t) { return t == INTTK; }
	pair<bool, GCompUnit*> ParseCompUnit() {
		auto *ret = new GCompUnit();
		// TODO: detect funcdef before decl
		while (fetchType() != NULLTK) {
			bool s = false;
			switch (fetchType()) {
				case CONSTTK:
					s = lAccept(ret, ParseDecl);
					break;
				case INTTK:
					if (fetchType(1) == MAINTK) s = lAccept(ret, ParseMainFuncDef);
					else if (fetchType(1) == IDENFR) {
						if (fetchType(2) == LPARENT) s = lAccept(ret, ParseFuncDef);
						else s = lAccept(ret, ParseDecl);
					}
					break;
				case VOIDTK:
					s = lAccept(ret, ParseFuncDef);
					break;
				default: break;
			}
			if (!s) break;
		}
		return make_pair(true, ret);
	}
	pair<bool, GDecl*> ParseDecl() {
		auto *ret = new GDecl();
		switch (fetchType()) {
			case CONSTTK:
				lAccept(ret, ParseConstDecl);
				break;
			case INTTK:
				lAccept(ret, ParseVarDecl);
				break;
			default:
				break;
		}
		return make_pair(true, ret);
	}
	pair<bool, GConstDecl*> ParseConstDecl() {
		auto *ret = new GConstDecl();
		lConsume(ret, CONSTTK);
		lAccept(ret, ParseBType);
		lAccept(ret, ParseConstDef);
		while (fetchType() == COMMA) {
			lConsume(ret, COMMA);
			lAccept(ret, ParseConstDef);
		}
		lConsumeOrReport(ret, SEMICN, 'I');
		return make_pair(true, ret);
	}
	pair<bool, GBType*> ParseBType() {
		auto *ret = new GBType();
		lConsume(ret, INTTK);
		return make_pair(true, ret);
	}
	pair<bool, GConstDef*> ParseConstDef() {
		auto *ret = new GConstDef();
		lConsume(ret, IDENFR);
		while (fetchType() == LBRACK) {
			lConsume(ret, LBRACK);
			lAccept(ret, ParseConstExp);
			lConsumeOrReport(ret, RBRACK, 'K');
		}
		lConsume(ret, ASSIGN);
		lAccept(ret, ParseConstInitVal);
		return make_pair(true, ret);
	}
	pair<bool, GConstInitVal*> ParseConstInitVal() {
		auto *ret = new GConstInitVal();
		if (fetchType() == LBRACE) {
			lConsume(ret, LBRACE);
			if (fetchType() != RBRACE) {
				lAccept(ret, ParseConstInitVal);
				while (fetchType() == COMMA) {
					lConsume(ret, COMMA);
					lAccept(ret, ParseConstInitVal);
				}
			}
			lConsume(ret, RBRACE);
		} else {
			lAccept(ret, ParseConstExp);
		}
		return make_pair(true, ret);
	}
	pair<bool, GVarDecl*> ParseVarDecl() {
		auto *ret = new GVarDecl();
		lAccept(ret, ParseBType);
		lAccept(ret, ParseVarDef);
		while (fetchType() == COMMA) {
			lConsume(ret, COMMA);
			lAccept(ret, ParseVarDef);
		}
		lConsumeOrReport(ret, SEMICN, 'I');
		return make_pair(true, ret);
	}
	pair<bool, GVarDef*> ParseVarDef() {
		auto *ret = new GVarDef();
		lConsume(ret, IDENFR);
		while (fetchType() == LBRACK) {
			lConsume(ret, LBRACK);
			lAccept(ret, ParseConstExp);
			lConsumeOrReport(ret, RBRACK, 'K');
		}
		if (fetchType() == ASSIGN) {
			lConsume(ret, ASSIGN);
			lAccept(ret, ParseInitVal);
		}
		return make_pair(true, ret);
	}
	pair<bool, GInitVal*> ParseInitVal() {
		auto *ret = new GInitVal();
		if (fetchType() == LBRACE) {
			lConsume(ret, LBRACE);
			if (fetchType() != RBRACE) {
				lAccept(ret, ParseInitVal);
				while (fetchType() == COMMA) {
					lConsume(ret, COMMA);
					lAccept(ret, ParseInitVal);
				}
			}
			lConsume(ret, RBRACE);
		} else {
			lAccept(ret, ParseExp);
		}
		return make_pair(true, ret);
	}
	pair<bool, GFuncDef*> ParseFuncDef() {
		auto *ret = new GFuncDef();
		lAccept(ret, ParseFuncType);
		lConsume(ret, IDENFR);
		lConsume(ret, LPARENT);
		if (isBType(fetchType())) lAccept(ret, ParseFuncFParams);
		lConsumeOrReport(ret, RPARENT, 'J');
		lAccept(ret, ParseBlock);
		return make_pair(true, ret);
	}
	pair<bool, GMainFuncDef*> ParseMainFuncDef() {
		auto *ret = new GMainFuncDef();
		lConsume(ret, INTTK);
		lConsume(ret, MAINTK);
		lConsume(ret, LPARENT);
		lConsumeOrReport(ret, RPARENT, 'J');
		lAccept(ret, ParseBlock);
		return make_pair(true, ret);
	}
	pair<bool, GFuncType*> ParseFuncType() {
		auto *ret = new GFuncType();
		if (fetchType() == VOIDTK) lConsume(ret, VOIDTK);
		else lConsume(ret, INTTK);
		return make_pair(true, ret);
	}
	pair<bool, GFuncFParams*> ParseFuncFParams() {
		auto *ret = new GFuncFParams();
		lAccept(ret, ParseFuncFParam);
		while (fetchType() == COMMA) {
			lConsume(ret, COMMA);
			lAccept(ret, ParseFuncFParam);
		}
		return make_pair(true, ret);
	}
	pair<bool, GFuncFParam*> ParseFuncFParam() {
		auto *ret = new GFuncFParam();
		lAccept(ret, ParseBType);
		lConsume(ret, IDENFR);
		if (fetchType() == LBRACK) {
			lConsume(ret, LBRACK);
			lConsumeOrReport(ret, RBRACK, 'K');
			while (fetchType() == LBRACK) {
				lConsume(ret, LBRACK);
				lAccept(ret, ParseConstExp);
				lConsumeOrReport(ret, RBRACK, 'K');
			}
		}
		return make_pair(true, ret);
	}
	pair<bool, GBlock*> ParseBlock() {
		auto *ret = new GBlock();
		lConsume(ret, LBRACE);
		while (fetchType() != RBRACE) {
			lAccept(ret, ParseBlockItem);
		}
		lConsume(ret, RBRACE);
		return make_pair(true, ret);
	}
	pair<bool, GBlockItem*> ParseBlockItem() {
		auto *ret = new GBlockItem();
		switch (fetchType()) {
			case CONSTTK:
			case INTTK:
				lAccept(ret, ParseDecl);
				break;
			default:
				lAccept(ret, ParseStmt);
				break;
		}
		return make_pair(true, ret);
	}
	pair<bool, GStmt*> ParseStmt() {
		auto *ret = new GStmt();
		switch (fetchType()) {
			case LBRACE:
				lAccept(ret, ParseBlock);
				break;
			case IFTK:
				lConsume(ret, IFTK);
				lConsume(ret, LPARENT);
				lAccept(ret, ParseCond);
				lConsumeOrReport(ret, RPARENT, 'J');
				lAccept(ret, ParseStmt);
				if (fetchType() == ELSETK) {
					lConsume(ret, ELSETK);
					lAccept(ret, ParseStmt);
				}
				break;
			case WHILETK:
				lConsume(ret, WHILETK);
				lConsume(ret, LPARENT);
				lAccept(ret, ParseCond);
				lConsumeOrReport(ret, RPARENT, 'J');
				lAccept(ret, ParseStmt);
				break;
			case BREAKTK:
				lConsume(ret, BREAKTK);
				lConsumeOrReport(ret, SEMICN, 'I');
				break;
			case CONTINUETK:
				lConsume(ret, CONTINUETK);
				lConsumeOrReport(ret, SEMICN, 'I');
				break;
			case RETURNTK:
				lConsume(ret, RETURNTK);
				if (isFiExp(fetchType())) lAccept(ret, ParseExp);
				lConsumeOrReport(ret, SEMICN, 'I');
				break;
			case PRINTFTK:
				lConsume(ret, PRINTFTK);
				lConsume(ret, LPARENT);
				lConsume(ret, STRCON);
				while (fetchType() == COMMA) {
					lConsume(ret, COMMA);
					lAccept(ret, ParseExp);
				}
				lConsumeOrReport(ret, RPARENT, 'J');
				lConsumeOrReport(ret, SEMICN, 'I');
				break;
			default:
				bool hasAssign = false;
				bool isGetint = false;
				for (int i = 0, t, bracket = 0; t = fetchType(i), t != NULLTK && !isKwToken(t) && !isBrace(t)
				                                                  && t != STRCON && t != PRINTFTK && t != SEMICN; ++i) { // TODO: Ambiguity here
					if (t == LBRACK) ++bracket;
					else if (t == RBRACK) --bracket;
					else if (t == ASSIGN) {
						hasAssign = true;
						isGetint = fetchType(i + 1) == GETINTTK;
						break;
					} else if (t == IDENFR && i > 0) { // if cannot be joined into exp, out
						TokenType tt = fetchType(i - 1);
						if (bracket == 0) break;
						if (tt == INTCON || tt == GETINTTK || tt == ASSIGN || tt == RBRACK) break;
					}
				}
				if (!hasAssign) {
					if (isFiExp(fetchType())) lAccept(ret, ParseExp);
					lConsumeOrReport(ret, SEMICN, 'I');
				} else if (isGetint) {
					lAccept(ret, ParseLVal);
					lConsume(ret, ASSIGN);
					lConsume(ret, GETINTTK);
					lConsume(ret, LPARENT);
					lConsumeOrReport(ret, RPARENT, 'J');
					lConsumeOrReport(ret, SEMICN, 'I');
				} else {
					lAccept(ret, ParseLVal);
					lConsume(ret, ASSIGN);
					lAccept(ret, ParseExp);
					lConsumeOrReport(ret, SEMICN, 'I');
				}
				break;
		}
		return make_pair(true, ret);
	}
	pair<bool, GExp*> ParseExp() {
		auto *ret = new GExp();
		lAccept(ret, ParseAddExp);
		return make_pair(true, ret);
	}
	pair<bool, GCond*> ParseCond() {
		auto *ret = new GCond();
		lAccept(ret, ParseLOrExp);
		return make_pair(true, ret);
	}
	pair<bool, GLVal*> ParseLVal() {
		auto *ret = new GLVal();
		lConsume(ret, IDENFR);
		while (fetchType() == LBRACK) {
			lConsume(ret, LBRACK);
			lAccept(ret, ParseExp);
			lConsumeOrReport(ret, RBRACK, 'K');
		}
		return make_pair(true, ret);
	}
	pair<bool, GPrimaryExp*> ParsePrimaryExp() {
		auto *ret = new GPrimaryExp();
		switch (fetchType()) {
			case LPARENT:
				lConsume(ret, LPARENT);
				lAccept(ret, ParseExp);
				lConsumeOrReport(ret, RPARENT, 'J'); // class J should not be handled though
				break;
			case IDENFR:
				lAccept(ret, ParseLVal);
				break;
			case INTCON:
				lAccept(ret, ParseNumber);
				break;
			default: break;
		}
		return make_pair(true, ret);
	}
	pair<bool, GNumber*> ParseNumber() {
		auto *ret = new GNumber();
		lConsume(ret, INTCON);
		return make_pair(true, ret);
	}
	pair<bool, GUnaryExp*> ParseUnaryExp() {
		auto *ret = new GUnaryExp();
		switch (fetchType()) {
			case PLUS:
			case MINU:
			case NOT:
				lAccept(ret, ParseUnaryOp);
				lAccept(ret, ParseUnaryExp);
				break;
			case LPARENT:
			case INTCON:
				lAccept(ret, ParsePrimaryExp);
				break;
			case IDENFR:
				if (fetchType(1) == LPARENT) {
					lConsume(ret, IDENFR);
					lConsume(ret, LPARENT);
					int t = fetchType();
					if (isFiExp(t)) lAccept(ret, ParseFuncRParams); // because FRP can only start with Exp
					lConsumeOrReport(ret, RPARENT, 'J');
				} else {
					lAccept(ret, ParsePrimaryExp);
				}
				break;
			default: break;
		}
		return make_pair(true, ret);
	}
	pair<bool, GUnaryOp*> ParseUnaryOp() {
		auto *ret = new GUnaryOp();
		lConsume(ret, PLUS) || lConsume(ret, MINU) || lConsume(ret, NOT);
		return make_pair(true, ret);
	}
	pair<bool, GFuncRParams*> ParseFuncRParams() {
		auto *ret = new GFuncRParams();
		lAccept(ret, ParseExp);
		while (fetchType() == COMMA) {
			lConsume(ret, COMMA);
			lAccept(ret, ParseExp);
		}
		return make_pair(true, ret);
	}
	pair<bool, GMulExp*> ParseMulExp() {
		auto *ret = new GMulExp();
		lAccept(ret, ParseUnaryExp);
		bool enough = false;
		while (!enough) {
			switch (fetchType()) {
				case MULT:
				case DIV:
				case MOD:
					lConsume(ret, MULT) || lConsume(ret, DIV) || lConsume(ret, MOD);
					lAccept(ret, ParseUnaryExp);
					break;
				default:
					enough = true;
					break;
			}
		}
		return make_pair(true, ret);
	}
	pair<bool, GAddExp*> ParseAddExp() {
		auto *ret = new GAddExp();
		lAccept(ret, ParseMulExp);
		bool enough = false;
		while (!enough) {
			switch (fetchType()) {
				case PLUS:
				case MINU:
					lConsume(ret, PLUS) || lConsume(ret, MINU);
					lAccept(ret, ParseMulExp);
					break;
				default:
					enough = true;
					break;
			}
		}
		return make_pair(true, ret);
	}
	pair<bool, GRelExp*> ParseRelExp() {
		auto *ret = new GRelExp();
		lAccept(ret, ParseAddExp);
		bool enough = false;
		while (!enough) {
			switch (fetchType()) {
				case LSS:
				case LEQ:
				case GRE:
				case GEQ:
					lConsume(ret, LSS) || lConsume(ret, LEQ) || lConsume(ret, GRE) || lConsume(ret, GEQ);
					lAccept(ret, ParseAddExp);
					break;
				default:
					enough = true;
					break;
			}
		}
		return make_pair(true, ret);
	}
	pair<bool, GEqExp*> ParseEqExp() {
		auto *ret = new GEqExp();
		lAccept(ret, ParseRelExp);
		bool enough = false;
		while (!enough) {
			switch (fetchType()) {
				case EQL:
				case NEQ:
					lConsume(ret, EQL) || lConsume(ret, NEQ);
					lAccept(ret, ParseRelExp);
					break;
				default:
					enough = true;
					break;
			}
		}
		return make_pair(true, ret);
	}
	pair<bool, GLAndExp*> ParseLAndExp() {
		auto *ret = new GLAndExp();
		lAccept(ret, ParseEqExp);
		while (fetchType() == AND) {
			lConsume(ret, AND);
			lAccept(ret, ParseEqExp);
		}
		return make_pair(true, ret);
	}
	pair<bool, GLOrExp*> ParseLOrExp() {
		auto *ret = new GLOrExp();
		lAccept(ret, ParseLAndExp);
		while (fetchType() == OR) {
			lConsume(ret, OR);
			lAccept(ret, ParseLAndExp);
		}
		return make_pair(true, ret);
	}
	pair<bool, GConstExp*> ParseConstExp() {
		auto *ret = new GConstExp();
		lAccept(ret, ParseAddExp);
		return make_pair(true, ret);
	}
}
namespace Err {
	using namespace ErrDefine;
	using namespace GraDefine;
	using namespace SymDefine;
	using namespace std;

	set<Function> FuncTab;
	map< string, vector<Function> > FuncMap;
	map< string, stack<Variable> > VarTab;
	set<Variable> GlobalVar;

	void addFunc(const Function &f, int line) {
		if (FuncTab.find(f) != FuncTab.end()) return report(line, 'B');
		else {
			FuncTab.insert(f);
			FuncMap[f.name].push_back(f);
		}
	}

	void addVar(set<Variable> &loc, const Variable &f, int line) {
		if (loc.find(f) != loc.end()) return report(line, 'B');
		else {
			loc.insert(f);
			VarTab[f.name].push(f);
		}
	}

	Variable lookupVar(const string &s) {
		const auto &it = VarTab.find(s);
		return it != VarTab.end() && !it->second.empty()
		       ? it->second.top() : ((Variable) {Void, Normal, ""});
	}

	void clearBlock(set<Variable> &v) {
		for (const auto &u : v) VarTab[u.name].pop();
	}

	void checkMandatoryReturn(GrammarElement *gb) {
		// check mandatory return (class G)
		int ln = get<0>(((GLexeme *) gb->sub.back())->t);
		if (gb->sub.size() == 2) report(ln, 'G');
		else {
			GrammarElement *gs = gb->sub[gb->sub.size() - 2]->sub[0];
			if (gs->_type != Stmt ||
			    gs->sub[0]->_type != Lexeme ||
			    get<1>(((GLexeme *) gs->sub[0])->t) != RETURNTK) report(ln, 'G');
		}
	}

	bool matchFunctionCall(const Function &f, const vector<Type> &pars) {
		for (size_t i = 0; i < f.pars.size(); ++i) if (f.pars[i] != pars[i]) return false;
		return true;
	}

	Type traverse(GrammarElement *ge, set<Variable> &loc = GlobalVar, Context con = {}) {
		set<Variable> newLoc;
		switch (ge->_type) {
			case CompUnit:
				for (const auto &g : ge->sub) traverse(g, loc, con);
				break;
			case Decl:
				for (const auto &g : ge->sub) traverse(g, loc, con);
				break;
			case ConstDecl:
				for (const auto &g : ge->sub) traverse(g, loc, con);
				break;
			case BType:
				return Int;
			case ConstDef:
			{
				const Token &t = ((GLexeme *) ge->sub[0])->t;
				auto dimCount = count_if(ge->sub.begin(), ge->sub.end(), [] (GrammarElement *p) { return p->_type == ConstExp; });
				addVar(loc, {(Type) (Int + dimCount), Const, get<2>(t)}, get<0>(t));
			}
				for (const auto &g : ge->sub) traverse(g, loc, con);
				break;
			case ConstInitVal:
				for (const auto &g : ge->sub) traverse(g, loc, con);
				break;
			case VarDecl:
				for (const auto &g : ge->sub) traverse(g, loc, con);
				break;
			case VarDef:
			{
				const Token &t = ((GLexeme *) ge->sub[0])->t;
				auto dimCount = count_if(ge->sub.begin(), ge->sub.end(), [] (GrammarElement *p) { return p->_type == ConstExp; });
				addVar(loc, {(Type) (Int + dimCount), Normal, get<2>(t)}, get<0>(t));
			}
				for (const auto &g : ge->sub) traverse(g, loc, con);
				break;
			case InitVal:
				for (const auto &g : ge->sub) traverse(g, loc, con);
				break;
			case FuncDef: {
				const Token &t1 = ((GLexeme *) ge->sub[1])->t;
				Type ret = traverse(ge->sub[0]); // no duplicate scan issue
				Function f {ret, get<2>(t1)};
				for (const auto &g : ge->sub) {
					if (g->_type == FuncFParams) {
						for (const auto &gg : g->sub) {
							if (gg->_type == FuncFParam) {
								auto pred = [] (GrammarElement *p) { return p->_type == Lexeme && get<1>(((GLexeme *) p)->t) == LBRACK; };
								auto dimCount = count_if(gg->sub.begin(), gg->sub.end(), pred);
								f.pars.push_back((Type) (Int + dimCount));
							}
						}
					}
				}
				addFunc(f, get<0>(t1));
				for (const auto &g : ge->sub) {
					if (g->_type != Block) {
						traverse(g, newLoc, con | (ret == Void ? Context::inVoidFunc : Context::inIntFunc));
					} else {
						for (const auto &gg : g->sub) { // = = same scope as the pars
							traverse(gg, newLoc, con | (ret == Void ? Context::inVoidFunc : Context::inIntFunc));
						}
					}
				}
				clearBlock(newLoc);
				if (ret != Void) checkMandatoryReturn(ge->sub.back());
				break;
			}
			case MainFuncDef:
				for (const auto &g : ge->sub) traverse(g, newLoc, con | Context::inIntFunc);
				clearBlock(newLoc);
				checkMandatoryReturn(ge->sub.back());
				break;
			case FuncType:
				return get<1>(((GLexeme *) ge->sub[0])->t) == VOIDTK ? Void : Int;
			case FuncFParams:
				for (const auto &g : ge->sub) traverse(g, loc, con);
				break;
			case FuncFParam:
			{
				const Token &t = ((GLexeme *) ge->sub[1])->t;
				auto pred = [] (GrammarElement *p) { return p->_type == Lexeme && get<1>(((GLexeme *) p)->t) == LBRACK; };
				auto dimCount = count_if(ge->sub.begin(), ge->sub.end(), pred);
				addVar(loc, {(Type) (Int + dimCount), Normal, get<2>(t)}, get<0>(t));
			}
				for (const auto &g : ge->sub) traverse(g, loc, con);
				break;
			case Block:
				for (const auto &g : ge->sub) traverse(g, newLoc, con);
				clearBlock(newLoc);
				break;
			case BlockItem:
				for (const auto &g : ge->sub) traverse(g, loc, con);
				break;
			case Stmt: {
				Context subCon = con;
				bool needCheckType = false; // for return [exp];
				GrammarElement *checkNode;
				Type expectedType;
				if (ge->sub[0]->_type == Lexeme) {
					const Token &t = ((GLexeme *) ge->sub[0])->t;
					switch (get<1>(t)) {
						case WHILETK:
							subCon = con | Context::inLoop;
							break;
						case BREAKTK:
						case CONTINUETK:
							if (!con.has(Context::inLoop)) report(get<0>(t), 'M');
							break;
						case PRINTFTK: {
							const Token &fmt = ((GLexeme *) ge->sub[2])->t;
							int ln = get<0>(fmt);
							const string &s = get<2>(fmt);
							auto pred = [] (GrammarElement *p) { return p->_type == Exp; };
							auto expCount = count_if(ge->sub.begin(), ge->sub.end(), pred);
							int fmtCount = 0;
							bool err = false;
							for (size_t i = 1; i + 1 < s.length(); ++i) { // " is included in fmtstr
								if (s[i] == 32 || s[i] == 33 || (40 <= s[i] && s[i] < 92) || (92 < s[i] && s[i] <= 126)) continue;
								else if (s[i] == 92) {
									if (s[i + 1] == 'n') continue;
									else err = true;
								} else if (s[i] == '%') {
									if (s[i + 1] == 'd') {
										++fmtCount;
										continue;
									}
									else err = true;
								} else err = true;
							}
							if (err) report(ln, 'A');
							if (fmtCount != expCount) report(get<0>(t), 'L');
							break;
						}
						case IFTK:
						case SEMICN:
							break;
						case RETURNTK: {
							if (ge->sub.size() == 1) {
								if (con.has(Context::inIntFunc)) panic("no return value in function returning int");
							}
							else {
								needCheckType = true;
								checkNode = ge->sub[1];
								if (con.has(Context::inIntFunc)) expectedType = Int;
								else expectedType = Void;
							}
							break;
						}
						default:
							panic("unexpected token at begin of statement");
							break;
					}
				} else if (ge->sub[0]->_type == LVal) {
					const Token &t = ((GLexeme *) ge->sub[0]->sub[0])->t;
					const auto &var = lookupVar(get<2>(t));
					if (var.cv == Const) report(get<0>(t), 'H');
				}
				for (const auto &g : ge->sub) {
					Type tt = traverse(g, loc, subCon);
					if (needCheckType && g == checkNode) {
						if (expectedType == Void && tt != Void)
							report(get<0>(((GLexeme *) ge->sub[0])->t), 'F');
						else if (expectedType == Int && tt != Int)
							panic("non-int return in function returning int");
					}
				}
				break;
			}
			case Exp:
			{
				Type t;
				for (const auto &g : ge->sub) t = traverse(g, loc, con);
				return t;
			}
			case Cond:
			{
				Type t;
				for (const auto &g : ge->sub) t = traverse(g, loc, con);
				return t;
			}
			case LVal:
			{
				const Token &t = ((GLexeme *) ge->sub[0])->t;
				auto pred = [] (GrammarElement *p) { return p->_type == Lexeme && get<1>(((GLexeme *) p)->t) == LBRACK; };
				auto dimCount = count_if(ge->sub.begin(), ge->sub.end(), pred);
				auto var = lookupVar(get<2>(t));
				Type ty;
				if (var.type == Void) report(get<0>(t), 'C'), ty = Any;
				else ty = (Type) (var.type - dimCount);
				for (const auto &g : ge->sub) traverse(g, loc, con);
				return ty;
			}
			case PrimaryExp:
			{
				Type t;
				for (const auto &g : ge->sub) t = g->_type == Lexeme ? t : traverse(g, loc, con);
				return t;
			}
			case Number:
				return Int;
			case UnaryExp: {
				Type ty;
				if (ge->sub[0]->_type == Lexeme) {
					const Token &t = ((GLexeme *) ge->sub[0])->t;
					auto it = FuncMap.find(get<2>(t));
					if (it == FuncMap.end()) {
						report(get<0>(t), 'C');
						ty = Any;
					} else {
						const auto &candi = it->second;
						vector<Type> rParams;
						bool lengthMatch = false;
						bool fullMatch = false;
						if (ge->sub.size() > 3) {
							GrammarElement *frp = ge->sub[2];
							for (size_t i = 0; i < frp->sub.size(); i += 2) {
								rParams.push_back(traverse(frp->sub[i], loc, con));
							}
						}
						for (const auto &f : candi) {
							if (f.pars.size() == rParams.size()) {
								lengthMatch = true;
								if (matchFunctionCall(f, rParams)) {
									fullMatch = true;
									ty = f.ret;
									break;
								}
							}
						}
						if (!lengthMatch) report(get<0>(t), 'D'), ty = Any;
						else if (!fullMatch) report(get<0>(t), 'E'), ty = Any;
					}
				} else {
					for (const auto &g : ge->sub) {
						Type tt = traverse(g, loc, con);
						if (g->_type == PrimaryExp) ty = tt;
						else if (g->_type == UnaryExp) {
							if (tt == Int || tt == Any) ty = tt;
							else panic("invalid type in unary-exp");
						}
					}
				}
				return ty;
			}
			case UnaryOp:
				for (const auto &g : ge->sub) traverse(g, loc, con);
				break;
			case FuncRParams:
				for (const auto &g : ge->sub) traverse(g, loc, con); // handled by match
				break;
			case MulExp:
			{
				Type ty;
				bool inv = true;
				for (const auto &g : ge->sub) {
					Type tt = traverse(g, loc, con);
					if (g->_type != Lexeme) {
						if (inv) ty = tt;
						else if (ty != Int || tt != Int) panic("non-int operand in mul-exp");
					}
				}
				return ty;
			}
			case AddExp:
			{
				Type ty;
				bool inv = true;
				for (const auto &g : ge->sub) {
					Type tt = traverse(g, loc, con);
					if (g->_type != Lexeme) {
						if (inv || ty == Int) ty = tt;
						else if (ty == Void || tt == Void) panic("void operand in add-exp");
						else if (tt != Int) panic("2 array operands in add-exp");
					}
				}
				return ty;
			}
			case RelExp:
			case EqExp:
			{
				Type ty;
				bool inv = true;
				for (const auto &g : ge->sub) {
					Type tt = traverse(g, loc, con);
					if (g->_type != Lexeme) {
						if (inv) ty = tt;
						else if (ty == Void || tt == Void) panic("void operand in compare");
						else if (ty != tt) panic("cannot compare operands with different types");
						else ty = Int;
					}
				}
				return ty;
			}
			case LAndExp:
			case LOrExp:
			{
				Type ty;
				bool inv = true;
				for (const auto &g : ge->sub) {
					Type tt = traverse(g, loc, con);
					if (g->_type != Lexeme) {
						if (inv) ty = tt;
						else if (ty == Void || tt == Void) panic("void operand in bitwise operation");
						else if (ty != Int || tt != Int) panic("array type in bitwise operation");
						else ty = Int;
					}
				}
				return ty;
			}
			case ConstExp:
			{
				Type t;
				for (const auto &g : ge->sub) t = traverse(g, loc, con);
				return t;
			}
			case Lexeme:
//				panic("single lexeme does not make sense");
				break;
			case General:
				panic("where does this shit come from?");
				break;
		}
//		if (ge->_type != Lexeme) for (const auto &g : ge->sub) traverse(g, loc, con);
		return Void;
	}
}
int main() {
	using namespace LexDefine;
	using namespace GraDefine;
	using namespace std;
	FILE *fIn = fopen("testfile.txt", "rb");
#ifndef LOCAL_DEBUG
	FILE *fOut = fopen("output.txt", "wb");
	FILE *fErr = fopen("error.txt", "wb");
#endif
	int r;
	r = Lex::main(fIn);
	r = Gra::main(Lex::tokens);
	Err::traverse(Gra::AST);
	map<char, string> errorMessage{
			{'A', "invalid character in format string"},
			{'B', "redefinition of variable"},
			{'C', "use of undeclared identifier"},
			{'D', "function parameter number mismatch"},
			{'E', "function parameter type mismatch"},
			{'F', "void function should not return a value"},
			{'G', "non-void function should return a value"},
			{'H', "cannot assign to variable with const-qualified type"},
			{'I', "expected ;"},
			{'J', "expected )"},
			{'K', "expected ]"},
			{'L', "printf argument number mismatch"},
			{'M', "break/continue not in loop statement"},
	};
	sort(ErrDefine::errors.begin(), ErrDefine::errors.end());
	for (auto u : ErrDefine::errors) {
#ifdef LOCAL_DEBUG
		printf("%d %c %s\n", u.first, tolower(u.second), errorMessage[u.second].c_str());
#else
		fprintf(fErr, "%d %c\n", u.first, tolower(u.second));
#endif
	}
#ifndef LOCAL_DEBUG
	return 0;
#endif
	function<void(GrammarElement *)> traverse = [&] (GrammarElement *ge) {
		if (ge->_type == Lexeme) {
			const Token &u = ((GLexeme *) ge)->t;
#ifdef LOCAL_DEBUG
			printf("%d %s %s\n", get<0>(u), TokenTypeName[get<1>(u)].c_str(), get<2>(u).c_str());
#else
			fprintf(fOut, "%s %s\n", TokenTypeName[get<1>(u)].c_str(), get<2>(u).c_str());
#endif
		} else {
			for (auto &&g : ge->sub) {
				if (g->_type == Lexeme) {

					switch (ge->_type) {
						case MulExp:
						case AddExp:
						case RelExp:
						case EqExp:
						case LAndExp:
						case LOrExp:
#ifdef LOCAL_DEBUG
							printf("<%s>\n", ge->_name.c_str());
#else
							fprintf(fOut, "<%s>\n", ge->_name.c_str());
#endif
							break;
						default:
							break;
					}
				}
				traverse(g);
			}
			if (ge->_type != BlockItem && ge->_type != Decl && ge->_type != BType) {
#ifdef LOCAL_DEBUG
				printf("<%s>\n", ge->_name.c_str());
#else
				fprintf(fOut, "<%s>\n", ge->_name.c_str());
#endif
			}
		}
	};
#ifdef LOCAL_DEBUG
	if (r == 0) traverse(Gra::AST);
#endif
	return 0;
}