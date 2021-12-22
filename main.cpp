#include <bits/stdc++.h>
#include "main.h"
namespace GenDefine {
	using namespace std;

	enum ValueType {
		None, Label, Glo, Stk, Ptr, IntL // Str
	};

//	int newStr () {
//		static int ret = 0;
//		return ++ret;
//	}

	int newLabel () {
		static int ret = 0;
		return ++ret;
	}

	int newVar () { // glo, stk, ptr, intl
		static int ret = 0;
		return ++ret;
	}

	enum Type {
		Int, IntArray, IntArrayArray
	};

	enum CV {
		Normal, Const
	};

	struct Variable { // NOLINT(cppcoreguidelines-pro-type-member-init)
		Type type;
		CV cv;
		string name;
		int id, dim1, dim2;
		bool operator < (const Variable &o) const { return name < o.name; }
	};

	struct Function {
		string name;
		vector<Type> pars;
		bool operator < (const Function &o) const {
			if (name == o.name) {
				if (pars.size() != o.pars.size()) return pars.size() < o.pars.size();
				else {
					for (size_t i = 0; i < pars.size(); ++i) if (pars[i] != o.pars[i]) return pars[i] < o.pars[i];
					return false;
				}
			} else return name < o.name;
		}
	};

	struct Value {
		ValueType type;
		int id;
	};

	struct Storage { // NOLINT(cppcoreguidelines-pro-type-member-init)
		int val;
		vector<int> valV;
		vector< vector<int> > valVV;
	};

	struct Stack {
		string func;
		int size;
		int alloc(int x) {
			return size -= x;
		}
	};

	using ConstExpr = int;

	struct Context {
		Value breakLabel = {Label, 0};
		Value continueLabel = {Label, 0};
	};
}
namespace OptDefine {
	using namespace std;
	using namespace ErrDefine;

	using udword = unsigned long long;
	using uword = unsigned int;

	const int N = 32;
	udword m;
	int l, sh_post;

	void chooseMultiplier(uword d, int prec) {
		uword t_d = d;
		while (__builtin_popcount(t_d) > 1) t_d += t_d & (-t_d);
		l = sh_post = __builtin_ctz(t_d);
		udword m_low = (((udword) 1) << N) + ((((udword) 1) << (N + l)) - (((udword) 1) << N) * d) / d;
		udword m_high = (((udword) 1) << N) + ((((udword) 1) << (N + l)) + (((udword) 1) << (N + l - prec)) - (((udword) 1) << N) * d) / d;
		if (m_low >= m_high || m_low < 0 || m_high < 0) panic("implementation error");
		while (m_low / 2 < m_high / 2 && sh_post > 0) {
			m_low >>= 1;
			m_high >>= 1;
			--sh_post;
		}
		m = m_high;
	}

	void divByConstant (vector<string> &program, const string &reg, int d) {
		uword absD = abs(d);
		chooseMultiplier(absD, N - 1);
		if (absD == 1) ;
		else if (absD == 1u << l) {
			program.emplace_back("sra $k0, " + reg + ", " + to_string(l - 1));
			program.emplace_back("srl $k0, $k0, " + to_string(N - l));
			program.emplace_back("add $k0, $k0, " + reg);
			program.emplace_back("sra " + reg + ", $k0, " + to_string(l));
		} else if (m < (((udword) 1) << (N - 1))) {
			program.emplace_back("li $k0, " + to_string(m));
			program.emplace_back("mult $k0, " + reg);
			program.emplace_back("mfhi $k0");
			program.emplace_back("sra $k0, $k0, " + to_string(sh_post));
			program.emplace_back("srl " + reg + ", " + reg + ", " + to_string(N - 1));
			program.emplace_back("add " + reg + ", " + reg + ", $k0");
		} else {
			program.emplace_back("li $k0, " + to_string((int) (m - (((udword) 1) << N))));
			program.emplace_back("mult $k0, " + reg);
			program.emplace_back("mfhi $k0");
			program.emplace_back("add $k0, $k0, " + reg);
			program.emplace_back("sra $k0, $k0, " + to_string(sh_post));
			program.emplace_back("srl " + reg + ", " + reg + ", " + to_string(N - 1));
			program.emplace_back("add " + reg + ", " + reg + ", $k0");
		}
		if (d < 0) program.emplace_back("negu " + reg + ", " + reg);
	}

	void remByConstant (vector<string> &program, const string &reg, int d) {
		program.emplace_back("move $k1, " + reg);
		divByConstant(program, "$k1", d);
		program.emplace_back("mul $k1, $k1, " + to_string(d));
		program.emplace_back("subu " + reg + ", " + reg + ", $k1");
	}
}
namespace Gen {
	using namespace GenDefine;
	using namespace ErrDefine;
	using namespace GraDefine;

	Value GenCompUnit(GCompUnit *g);
	Value GenDecl(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenConstDecl(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
//	Value GenBType(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenConstDef(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
//	Value GenConstInitVal(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenVarDecl(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenVarDef(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
//	Value GenInitVal(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenFuncDef(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenMainFuncDef(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
//	Value GenFuncType(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenFuncFParams(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
//	Value GenFuncFParam(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenBlock(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenBlockItem(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenStmt(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenCond(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenLVal(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenPrimaryExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenNumber(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenUnaryExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
//	Value GenUnaryOp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
//	Value GenFuncRParams(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenMulExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenAddExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenRelExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenEqExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenLAndExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	Value GenLOrExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);

	ConstExpr EvalConstExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);

	ConstExpr EvalExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	ConstExpr EvalLVal(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	ConstExpr EvalPrimaryExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	ConstExpr EvalNumber(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	ConstExpr EvalUnaryExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
//	ConstExpr EvalUnaryOp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	ConstExpr EvalMulExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);
	ConstExpr EvalAddExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx);

	void fillStackSizes();

	vector<string> data;
	vector<string> program;
	vector< pair<int, string> > fillStackSizeTask;
	map< string, int > stackSizes;

	set< Variable > globalVar; // global loc
	map< string, stack<Variable> > varTab;
	map< string, Function > funcMap;

//	map< int, Variable > constVarMap;
	map< int, Storage > storageMap; // maps var to its compile-time storage, if it is const

	set< int > tempVarSet; // for temporary Int on stack
	map< int, Variable > variableMap; // for all, glo / stk / ptr
	map< int, ValueType > valueTypeMap; // get value type by its id (fetched from Variable)
	map< int, int > stkOffsetMap; // for stk and ptr
	map< int, int > intLiteralMap; // for integer literals
	set< int > intPtrSet; // for all ptr

	string loadAddress(const Value &v, const string &reg) {
		switch (v.type) {
			case None:
			case IntL:
				panic("loading address of none or literal");
			case Label:
				return "la " + reg + ", l_" + to_string(v.id);
			case Glo:
				return "la " + reg + ", g_" + to_string(v.id);
			case Stk:
				return "addiu " + reg + ", $sp, " + to_string(stkOffsetMap[v.id]);
			case Ptr:
				return "lw " + reg + ", " + to_string(stkOffsetMap[v.id]) + "($sp)";
		}
		return "";
	}

	inline void emitLabel(int id) {
		program.emplace_back("l_" + to_string(id) + ":");
	}

	string loadValue(const Value &v, const string &reg) {
		switch (v.type) {
			case None:
				panic("loading none type");
			case IntL:
				return "li " + reg + ", " + to_string(intLiteralMap[v.id]);
			case Label:
				return "la " + reg + ", l_" + to_string(v.id);
			case Glo:
				return "lw " + reg + ", g_" + to_string(v.id);
			case Stk:
				if (tempVarSet.count(v.id) > 0 || variableMap.find(v.id)->second.type == Int)
					return "lw " + reg + ", " + to_string(stkOffsetMap[v.id]) + "($sp)";
				else return "addiu " + reg + ", $sp, " + to_string(stkOffsetMap[v.id]);
			case Ptr:
				return "lw " + reg + ", " + to_string(stkOffsetMap[v.id]) + "($sp)";
		}
		return "";
	}

	void loadLVal(const Value &v, const string &reg) {
		program.emplace_back(loadValue(v, reg));
		if (v.type == Ptr && intPtrSet.count(v.id) > 0)
			program.emplace_back("lw " + reg + ", (" + reg + ")");
	}

	string storeOnStack(int offset, const string &reg) {
		return "sw " + reg + ", " + to_string(offset) + "($sp)";
	}

//	string storeValue(const Value &v, const string &reg) {
//		switch (v.type) {
//			case None:
////			case Str:
//			case Label:
//				panic("store to non-var");
//			case Ptr:
//				panic("store to ptr");
//			case Glo:
//				return "sw " + reg + ", g_" + to_string(v.id);
//			case Stk:
//				return "lw " + reg + ", " + to_string(stkOffsetMap[v.id]) + "($sp)";
//		}
//	}

	void syscall_putchar(char i) {
		program.push_back("li $a0, " + to_string(i));
		program.emplace_back("li $v0, 11");
		program.emplace_back("syscall");
	}

	void syscall_putint(const string &reg) {
		program.push_back("move $a0, " + reg);
		program.emplace_back("li $v0, 1");
		program.emplace_back("syscall");
	}

	void syscall_getint() {
		program.emplace_back("li $v0, 5");
		program.emplace_back("syscall");
	}

	void addVar(set<Variable> &loc, const Variable &f) {
		loc.insert(f);
		varTab[f.name].push(f);
	}

	Variable lookupVar(const string &s) { return varTab.find(s)->second.top(); } // should exist

	void clearBlock(set<Variable> &v) { for (const auto &u : v) varTab[u.name].pop(); }

	Value GenCompUnit(GCompUnit *g) {
		for (auto gg : g->sub) {
			if (gg->_type == Decl) {
				Stack s = {"", 0};
				Context ctx;
				GenDecl(gg, globalVar, s, ctx);
			} else if (gg->_type == FuncDef) {
				Stack s = {get<2>(((GLexeme *) gg->sub[1])->t), 0};
				Context ctx;
				GenFuncDef(gg, globalVar, s, ctx);
				stackSizes[s.func] = -s.size;
			} else {
				Stack s = {"main", 0};
				Context ctx;
				GenMainFuncDef(gg, globalVar, s, ctx);
				stackSizes["main"] = -s.size;
			}
		}
		fillStackSizes();
		return {None, 0};
	}

	Value GenDecl(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		for (auto gg : g->sub) {
			if (gg->_type == ConstDecl) {
				GenConstDecl(gg, loc, s, ctx);
			} else {
				GenVarDecl(gg, loc, s, ctx);
			}
		}
		return {None, 0};
	}

	Value GenConstDecl(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		for (auto gg : g->sub) {
			if (gg->_type == ConstDef) {
				GenConstDef(gg, loc, s, ctx);
			}
		}
		return {None, 0};
	}

//	Value GenBType(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
//		return {None, 0};
//	}

	Value GenConstDef(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		const Token &t = ((GLexeme *) g->sub[0])->t;
		auto dimCount = count_if(g->sub.begin(), g->sub.end(), [] (GrammarElement *p) { return p->_type == ConstExp; });
		int dim1 = 1, dim2 = 1;
		if (dimCount >= 1) dim1 = EvalConstExp((GConstExp *) g->sub[2], loc, s, ctx);
		if (dimCount >= 2) dim2 = EvalConstExp((GConstExp *) g->sub[5], loc, s, ctx);
		int id = newVar();
		Variable v{(Type) (Int + dimCount), Const, get<2>(t), id, dim1, dim2};
		valueTypeMap[id] = Glo;
		variableMap[id] = v;
		addVar(loc, v);
		data.push_back("g_" + to_string(id) + ":"); // label
		storageMap[id] = {0, vector<int>(dim1), vector< vector<int> >(dim1, vector<int>(dim2))};
		Storage &sto = storageMap[id];
		if (dimCount == 2) {
			for (auto gg : g->sub) {
				int i = 0;
				if (gg->_type == ConstInitVal) for (auto ggg : gg->sub) { // aa
					if (ggg->_type == ConstInitVal) {
						int j = 0;
						for (auto g4 : ggg->sub) { // a
							if (g4->_type == ConstInitVal) {
								for (auto g5 : g4->sub) { // i
									sto.valVV[i][j] = EvalConstExp((GConstExp *) g5, loc, s, ctx);
									data.push_back(".word " + to_string(sto.valVV[i][j]));
								}
								++j;
							}
						}
						++i;
					}
				}
			}
		} else if (dimCount == 1) {
			for (auto gg : g->sub) {
				int i = 0;
				if (gg->_type == ConstInitVal) for (auto ggg : gg->sub) { // a
					if (ggg->_type == ConstInitVal) for (auto g4 : ggg->sub) { // i
						sto.valV[i] = EvalConstExp((GConstExp *) g4, loc, s, ctx);
						data.push_back(".word " + to_string(sto.valV[i]));
						++i;
					}
				}
			}
		} else {
			for (auto gg : g->sub) {
				if (gg->_type == ConstInitVal) for (auto ggg : gg->sub) { // i
					sto.val = EvalConstExp((GConstExp *) ggg, loc, s, ctx);
					data.push_back(".word " + to_string(sto.val));
				}
			}
		}
		storageMap[id] = sto;
		return {Glo, id};
	}

//	Value GenConstInitVal(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
//		return {None, 0};
//	}

	Value GenVarDecl(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		for (auto gg : g->sub) {
			if (gg->_type == VarDef) {
				GenVarDef(gg, loc, s, ctx);
			}
		}
		return {None, 0};
	}

	Value GenVarDef(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		const Token &t = ((GLexeme *) g->sub[0])->t;
		auto dimCount = count_if(g->sub.begin(), g->sub.end(), [] (GrammarElement *p) { return p->_type == ConstExp; });
		int dim1 = 1, dim2 = 1, size = 4;
		if (dimCount >= 1) dim1 = EvalConstExp((GConstExp *) g->sub[2], loc, s, ctx), size = 4 * dim1;
		if (dimCount >= 2) dim2 = EvalConstExp((GConstExp *) g->sub[5], loc, s, ctx), size = 4 * dim1 * dim2;
		bool global = s.func.empty();
		if (!global) {
			int id = newVar();
			Variable v{(Type) (Int + dimCount), Normal, get<2>(t), id, dim1, dim2};
			valueTypeMap[id] = Stk;
			variableMap[id] = v;
			int offset = s.alloc(size);
			stkOffsetMap[id] = offset;
			addVar(loc, v);
			if (dimCount == 2) {
				for (auto gg : g->sub) {
					int i = 0;
					if (gg->_type == InitVal) for (auto ggg : gg->sub) {
						if (ggg->_type == InitVal) { // a
							int j = 0;
							for (auto g4 : ggg->sub) {
								if (g4->_type == InitVal) {
									for (auto g5 : g4->sub) { // i
										Value vv = GenExp((GExp *) g5, loc, s, ctx);
										loadLVal(vv, "$t0");
										program.push_back(storeOnStack(offset + 4 * (i * dim2 + j), "$t0"));
									}
									++j;
								}
							}
							++i;
						}
					}
				}
			} else if (dimCount == 1) {
				for (auto gg : g->sub) {
					int i = 0;
					if (gg->_type == InitVal) for (auto ggg : gg->sub) { // a
							if (ggg->_type == InitVal) for (auto g4 : ggg->sub) { // i
									Value vv = GenExp((GExp *) g4, loc, s, ctx);
									loadLVal(vv, "$t0");
									program.push_back(storeOnStack(offset + 4 * i, "$t0"));
									++i;
								}
						}
				}
			} else {
				for (auto gg : g->sub) {
					if (gg->_type == InitVal) for (auto ggg : gg->sub) { // i
							Value vv = GenExp((GExp *) ggg, loc, s, ctx);
							loadLVal(vv, "$t0");
							program.push_back(storeOnStack(offset, "$t0"));
						}
				}
			}
			return {Stk, id};
		} else {
			int id = newVar();
			Variable v{(Type) (Int + dimCount), Normal, get<2>(t), id, dim1, dim2};
			addVar(loc, v);
			valueTypeMap[id] = Glo;
			variableMap[id] = v;
			bool init = count_if(g->sub.begin(), g->sub.end(), [] (GrammarElement *p) { return p->_type == InitVal; }) > 0;
			if (!init) {
				data.push_back("g_" + to_string(id) + ": .space " + to_string(size));
				return {Glo, id};
			} else {
				data.push_back("g_" + to_string(id) + ":");
				if (dimCount == 2) {
					for (auto gg : g->sub) {
						if (gg->_type == InitVal) {
							int i = 0;
							for (auto ggg : gg->sub) { // aa
								if (ggg->_type == InitVal) {
									int j = 0;
									for (auto g4 : ggg->sub) { // a
										if (g4->_type == InitVal) {
											for (auto g5 : g4->sub) { // i
												ConstExpr vv = EvalExp((GExp *) g5, loc, s, ctx);
												data.push_back(".word " + to_string(vv));
											}
											++j;
										}
									}
									++i;
								}
							}
						}
					}
				} else if (dimCount == 1) {
					for (auto gg : g->sub) {
						int i = 0;
						if (gg->_type == InitVal) for (auto ggg : gg->sub) { // a
								if (ggg->_type == InitVal) for (auto g4 : ggg->sub) { // i
										ConstExpr vv = EvalExp((GExp *) g4, loc, s, ctx);
										data.push_back(".word " + to_string(vv));
										++i;
									}
							}
					}
				} else {
					for (auto gg : g->sub) {
						if (gg->_type == InitVal) for (auto ggg : gg->sub) { // i
							ConstExpr vv = EvalExp((GExp *) ggg, loc, s, ctx);
							data.push_back(".word " + to_string(vv));
						}
					}
				}
				return {Glo, id};
			}
		}
	}

//	Value GenInitVal(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
//		return {None, 0};
//	}

	Value GenFuncDef(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		set<Variable> newLoc;
		string name = get<2>(((GLexeme *) g->sub[1])->t);
		program.push_back("f_" + name + ":");
		if (count_if(g->sub.begin(), g->sub.end(), [] (GrammarElement *gg) { return gg->_type == FuncFParams; }) == 0) {
			funcMap[name] = { name };
		}
		for (const auto &gg : g->sub) {
			if (gg->_type == FuncFParams) { GenFuncFParams((GFuncFParams *) gg, newLoc, s, ctx); }
			else if (gg->_type == Block) {
				GenBlock((GBlock *) gg, newLoc, s, ctx);
			}
		}
		program.emplace_back("jr $ra");
		clearBlock(newLoc);
		return {None, 0};
	}

	Value GenMainFuncDef(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		set<Variable> newLoc;
		program.emplace_back("f_main:");
		funcMap["main"] = {"main"};
		for (const auto &gg : g->sub) {
			if (gg->_type == Block) {
				GenBlock((GBlock *) gg, newLoc, s, ctx);
			}
		}
		clearBlock(newLoc);
		return {None, 0};
	}

//	Value GenFuncType(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
//		return {None, 0};
//	}

	Value GenFuncFParams(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		int paramCount = (int) count_if(g->sub.begin(), g->sub.end(), [] (GrammarElement *p) {
			return p->_type == FuncFParam;
		}); // stack: $ra params vars
		s.alloc(paramCount * 4);
		int i = 0;
		Function f {s.func};
		for (const auto &gg : g->sub) {
			if (gg->_type == FuncFParam) {
				++i;
				const Token &t = ((GLexeme *) gg->sub[1])->t;
				auto pred = [] (GrammarElement *p) { return p->_type == Lexeme && get<1>(((GLexeme *) p)->t) == LBRACK; };
				auto dimCount = count_if(gg->sub.begin(), gg->sub.end(), pred);
				f.pars.push_back((Type) (Int + dimCount)); // maintain function table
				int id = newVar();
				int dim1 = 1, dim2 = 1;
				if (dimCount >= 2) dim2 = EvalConstExp((GConstExp *) gg->sub[5], loc, s, ctx);
				Variable v {(Type) (Int + dimCount), Normal, get<2>(t), id, dim1, dim2};
				valueTypeMap[id] = dimCount > 0 ? Ptr : Stk;
				variableMap[id] = v;
				stkOffsetMap[id] = -4 * i;
				addVar(loc, v);
			}
		}
		funcMap[f.name] = f;
		return {None, 0};
	}

//	Value GenFuncFParam(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
//		return {None, 0};
//	}

	Value GenBlock(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		set<Variable> newLoc;
		for (const auto &gg : g->sub) {
			if (gg->_type == BlockItem) {
				GenBlockItem((GBlockItem *) gg, newLoc, s, ctx);
			}
		}
		clearBlock(newLoc);
		return {None, 0};
	}

	Value GenBlockItem(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		for (const auto &gg : g->sub) {
			if (gg->_type == Stmt) {
				GenStmt((GStmt *) gg, loc, s, ctx);
			} else {
				GenDecl((GDecl *) gg, loc, s, ctx);
			}
		}
		return {None, 0};
	}

	Value GenStmt(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		if (g->sub[0]->_type == Lexeme) {
			const Token &t = ((GLexeme *) g->sub[0])->t;
			switch (get<1>(t)) {
				case PRINTFTK: {
					const Token &fmt = ((GLexeme *) g->sub[2])->t;
					const string &str = get<2>(fmt);
					vector<Value> exps;
					for (const auto &gg : g->sub) {
						if (gg->_type == Exp) {
							exps.emplace_back(GenExp(gg, loc, s, ctx));
						}
					}
					int fmtCount = 0;
					for (size_t i = 1; i + 1 < str.length(); ++i) { // " is included in fmtstr
						if (str[i] == 32 || str[i] == 33 || (40 <= str[i] && str[i] < 92) || (92 < str[i] && str[i] <= 126)) {
							syscall_putchar(str[i]);
						}
						else if (str[i] == 92) {
							if (str[i + 1] == 'n') {
								++i;
								syscall_putchar('\n');
							}
						} else if (str[i] == '%') {
							if (str[i + 1] == 'd') {
								++i;
								loadLVal(exps[fmtCount], "$t0");
								syscall_putint("$t0");
								++fmtCount;
							}
						}
					}
					break;
				}
				case WHILETK: {
					int l1 = newLabel(), l2 = newLabel();
					emitLabel(l1);
					Value v = GenCond(g->sub[2], loc, s, ctx);
					loadLVal(v, "$t0");
					program.emplace_back("beqz $t0, l_" + to_string(l2));
					Context cc = ctx;
					cc.continueLabel = {Label, l1};
					cc.breakLabel = {Label, l2};
					GenStmt(g->sub[4], loc, s, cc);
					program.emplace_back("j l_" + to_string(l1));
					emitLabel(l2);
					break;
				}
				case BREAKTK:
					program.push_back("j l_" + to_string(ctx.breakLabel.id));
					break;
				case CONTINUETK:
					program.push_back("j l_" + to_string(ctx.continueLabel.id));
					break;
				case IFTK: {
					if (g->sub.size() <= 5) {
						int l1 = newLabel();
						Value v = GenCond(g->sub[2], loc, s, ctx);
						loadLVal(v, "$t0");
						program.emplace_back("beqz $t0, l_" + to_string(l1));
						GenStmt(g->sub[4], loc, s, ctx);
						emitLabel(l1);
					} else {
						int l1 = newLabel(), l2 = newLabel();
						Value v = GenCond(g->sub[2], loc, s, ctx);
						loadLVal(v, "$t0");
						program.emplace_back("beqz $t0, l_" + to_string(l1));
						GenStmt(g->sub[4], loc, s, ctx);
						program.emplace_back("j l_" + to_string(l2));
						emitLabel(l1);
						GenStmt(g->sub[6], loc, s, ctx);
						emitLabel(l2);
					}
					break;
				}
				case SEMICN:
					break;
				case RETURNTK: {
					if (g->sub[1]->_type != Exp) {
						program.emplace_back("jr $ra");
					} else {
						loadLVal(GenExp((GExp *) g->sub[1], loc, s, ctx), "$v0");
						program.emplace_back("jr $ra");
					}
					break;
				}
				default:
					panic("unexpected token at begin of statement");
					break;
			}
		} else if (g->sub[0]->_type == LVal) {
			Value lv = GenLVal(g->sub[0], loc, s, ctx);
			if ((int) g->sub.size() > 4) {
				syscall_getint();
				program.emplace_back(loadAddress(lv, "$t0"));
				program.emplace_back("sw $v0, ($t0)");
			} else {
				Value exp = GenExp(g->sub[2], loc, s, ctx);
				program.emplace_back(loadAddress(lv, "$t0"));
				loadLVal(exp, "$t1");
				program.emplace_back("sw $t1, ($t0)");
			}
		} else if (g->sub[0]->_type == Exp) {
			GenExp((GExp *) g->sub[0], loc, s, ctx);
		} else {
			GenBlock((GBlock *) g->sub[0], loc, s, ctx);
		}
		return {None, 0};
	}

	Value GenExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		return GenAddExp(g->sub[0], loc, s, ctx);
	}

	Value GenCond(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		return GenLOrExp(g->sub[0], loc, s, ctx);
	}

	// LVal will return a ptr, you just need to [load / store] it in place
	//
	Value GenLVal(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		int dimCount = (int) count_if(g->sub.begin(), g->sub.end(), [] (GrammarElement *gg) { return gg->_type == Exp; });
		const Variable &v = lookupVar(get<2>(((GLexeme *) g->sub[0])->t));
		vector<Value> exps;
		for (const auto &gg : g->sub) {
			if (gg->_type == Exp) {
				exps.emplace_back(GenExp(gg, loc, s, ctx));
			}
		}
		if (dimCount == 0) {
			if (v.type == Int) {
				return {valueTypeMap[v.id], v.id};
			} else {
				int id = newVar(), offset = s.alloc(4);
				valueTypeMap[id] = Ptr;
				stkOffsetMap[id] = offset;
//				if (v.type == Int) intPtrSet.insert(id);
				program.push_back(loadAddress({valueTypeMap[v.id], v.id}, "$t0"));
				program.push_back("sw $t0, " + to_string(offset) + "($sp)");
				return {Ptr, id};
			}
		} else if (v.type == IntArrayArray) {
			if (dimCount == 2) {
				int id = newVar(), offset = s.alloc(4);
				valueTypeMap[id] = Ptr;
				stkOffsetMap[id] = offset;
				intPtrSet.insert(id);
				program.push_back(loadAddress({valueTypeMap[v.id], v.id}, "$t0"));
				loadLVal(exps[0], "$t1");
				program.push_back("mul $t1, $t1, " + to_string(v.dim2 * 4));
				program.emplace_back("addu $t0, $t0, $t1");
				loadLVal(exps[1], "$t1");
				program.emplace_back("sll $t1, $t1, 2");
				program.emplace_back("addu $t0, $t0, $t1");
				program.push_back("sw $t0, " + to_string(offset) + "($sp)");
				return {Ptr, id};
			} else {
				int id = newVar(), offset = s.alloc(4);
				valueTypeMap[id] = Ptr;
				stkOffsetMap[id] = offset;
				program.push_back(loadAddress({valueTypeMap[v.id], v.id}, "$t0"));
				loadLVal(exps[0], "$t1");
				program.push_back("mul $t1, $t1, " + to_string(v.dim2 * 4));
				program.emplace_back("addu $t0, $t0, $t1");
				program.push_back("sw $t0, " + to_string(offset) + "($sp)");
				return {Ptr, id};
			}
		} else { // this must be array
			int id = newVar(), offset = s.alloc(4);
			valueTypeMap[id] = Ptr;
			stkOffsetMap[id] = offset;
			intPtrSet.insert(id);
			program.push_back(loadAddress({valueTypeMap[v.id], v.id}, "$t0"));
			loadLVal(exps[0], "$t1");
			program.emplace_back("sll $t1, $t1, 2");
			program.emplace_back("addu $t0, $t0, $t1");
			program.push_back("sw $t0, " + to_string(offset) + "($sp)");
			return {Ptr, id};
		}
	}

	Value GenPrimaryExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		if (g->sub.size() == 1) {
			if (g->sub[0]->_type == LVal) {
				return GenLVal(g->sub[0], loc, s, ctx);
			}
			else return GenNumber(g->sub[0], loc, s, ctx);
		} else {
			return GenExp(g->sub[1], loc, s, ctx);
		}
	}

	Value GenNumber(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		int value = stoi(get<2>(((GLexeme *) g->sub[0])->t));
		int id = newVar();
		valueTypeMap[id] = IntL;
		intLiteralMap[id] = value;
		return {IntL, id};
//		valueTypeMap[id] = Glo;
//		data.push_back("g_" + to_string(id) + ": .word " + to_string(value));
//		return {Glo, id};
	}

	Value GenUnaryExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		if (g->sub[0]->_type == PrimaryExp) return GenPrimaryExp(g->sub[0], loc, s, ctx);
		else if (get<1>(((GLexeme *) g->sub[0])->t) == IDENFR) {
			int id = newVar(), offset = s.alloc(4);
			valueTypeMap[id] = Stk;
			stkOffsetMap[id] = offset;
			tempVarSet.insert(id);
			// calling function
			const Function &called = funcMap[get<2>(((GLexeme *) g->sub[0])->t)];
			vector<Value> exps;
			if (g->sub.size() > 3) {
				for (const auto &gg : g->sub[2]->sub) {
					if (gg->_type == Exp) {
						exps.emplace_back(GenExp(gg, loc, s, ctx));
					}
				}
			}
			// we have all the params here
			program.emplace_back("addiu $fp, $sp, -%d"); // minus the stack, make the hole
			fillStackSizeTask.emplace_back((int) program.size() - 1, s.func); // set fill task
			// saving registers!
			program.emplace_back("sw $ra, ($fp)");
			// we can pass params now ^_^
			int i = 0;
			for (const auto &v : exps) {
				Type ty = called.pars[i];
				++i;
				loadLVal(v, "$t0");
				// check by value or by ref = = no need now
//				if (ty == Int) program.emplace_back("lw $t0, ($t0)"); // pass by value
				program.push_back("sw $t0, " + to_string(-4 * i) + "($fp)");
			}
			// change stack
			program.emplace_back("move $sp, $fp");
			// et voila! now we can call the func
			program.push_back("jal f_" + called.name);
			// restoring them
			program.emplace_back("lw $ra, ($sp)");
			program.emplace_back("addiu $sp, $sp, %d"); // add it back
			fillStackSizeTask.emplace_back((int) program.size() - 1, s.func);
			// finish calling, store return value onto stack
			program.push_back("sw $v0, " + to_string(offset) + "($sp)");
			return {Stk, id};
		} else {
			const Value &v = GenUnaryExp(g->sub[1], loc, s, ctx);
			TokenType op = get<1>(((GLexeme *) g->sub[0]->sub[0])->t);
			if (op != PLUS) {
				if (v.type == IntL) {
					int _ = newVar(), _v = op == MINU ? -intLiteralMap[v.id] : !intLiteralMap[v.id];
					valueTypeMap[_] = IntL;
					intLiteralMap[_] = _v;
					return {IntL, _};
				}
				int id = newVar(), offset = s.alloc(4);
				valueTypeMap[id] = Stk;
				stkOffsetMap[id] = offset;
				tempVarSet.insert(id);
				loadLVal(v, "$t0");
				program.emplace_back(op == MINU ? "negu $t0, $t0" : "sltiu $t0, $t0, 1");
				program.push_back(storeOnStack(offset, "$t0"));
				return {Stk, id};
			}
			else return v;
		}
	}

//	Value GenUnaryOp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
//		return {None, 0};
//	}
//
//	Value GenFuncRParams(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
//		return {None, 0};
//	}

	Value GenMulExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		if (g->sub.size() == 1) return GenUnaryExp(g->sub[0], loc, s, ctx);
		else {
			vector<Value> vs;
			for (int i = 0; i < (int) g->sub.size(); i += 2) vs.emplace_back(GenUnaryExp(g->sub[i], loc, s, ctx));
			for (int i = 0; i < (int) vs.size(); ++i) {
				const Value &v2 = vs[i];
				if (i == 0) {
					loadLVal(v2, "$t0");
				} else {
					TokenType tty = get<1>(((GLexeme *) g->sub[i * 2 - 1])->t);
					if (tty == MULT || v2.type != IntL) loadLVal(v2, "$t1");
					if (tty == MULT) program.emplace_back("mul $t0, $t0, $t1");
					else if (tty == DIV) {
						if (v2.type == IntL) OptDefine::divByConstant(program, "$t0", intLiteralMap[v2.id]);
						else program.emplace_back("div $t0, $t0, $t1");
					}
					else {
						if (v2.type == IntL) OptDefine::remByConstant(program, "$t0", intLiteralMap[v2.id]);
						else program.emplace_back("rem $t0, $t0, $t1");
					}
				}
			}
			int id = newVar(), offset = s.alloc(4);
			valueTypeMap[id] = Stk;
			stkOffsetMap[id] = offset;
			tempVarSet.insert(id);
			Value v = {Stk, id};
			program.emplace_back(storeOnStack(offset, "$t0"));
			return v;
		}
	}

	Value GenAddExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		if (g->sub.size() == 1) return GenMulExp(g->sub[0], loc, s, ctx);
		else {
			vector<Value> vs;
			for (int i = 0; i < (int) g->sub.size(); i += 2) vs.emplace_back(GenMulExp(g->sub[i], loc, s, ctx));
			for (int i = 0; i < (int) vs.size(); ++i) {
				const Value &v2 = vs[i];
				if (i == 0) {
					loadLVal(v2, "$t0");
				} else {
					loadLVal(v2, "$t1");
					TokenType tty = get<1>(((GLexeme *) g->sub[i * 2 - 1])->t);
					if (tty == PLUS) program.emplace_back("addu $t0, $t0, $t1");
					else program.emplace_back("subu $t0, $t0, $t1");
				}
			}
			int id = newVar(), offset = s.alloc(4);
			valueTypeMap[id] = Stk;
			stkOffsetMap[id] = offset;
			tempVarSet.insert(id);
			Value v = {Stk, id};
			program.emplace_back(storeOnStack(offset, "$t0"));
			return v;
		}
	}

	Value GenRelExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		if (g->sub.size() == 1) return GenAddExp(g->sub[0], loc, s, ctx);
		else {
			vector<Value> vs;
			for (int i = 0; i < (int) g->sub.size(); i += 2) vs.emplace_back(GenAddExp(g->sub[i], loc, s, ctx));
			for (int i = 0; i < (int) vs.size(); ++i) {
				const Value &v2 = vs[i];
				if (i == 0) {
					loadLVal(v2, "$t0");
				} else {
					loadLVal(v2, "$t1");
					TokenType tty = get<1>(((GLexeme *) g->sub[i * 2 - 1])->t);
					if (tty == LSS) program.emplace_back("slt $t0, $t0, $t1");
					else if (tty == GRE) program.emplace_back("sgt $t0, $t0, $t1");
					else if (tty == LEQ) program.emplace_back("sle $t0, $t0, $t1");
					else program.emplace_back("sge $t0, $t0, $t1");
				}
			}
			int id = newVar(), offset = s.alloc(4);
			valueTypeMap[id] = Stk;
			stkOffsetMap[id] = offset;
			tempVarSet.insert(id);
			Value v = {Stk, id};
			program.emplace_back(storeOnStack(offset, "$t0"));
			return v;
		}
	}

	Value GenEqExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		if (g->sub.size() == 1) return GenRelExp(g->sub[0], loc, s, ctx);
		else {
			vector<Value> vs;
			for (int i = 0; i < (int) g->sub.size(); i += 2) vs.emplace_back(GenRelExp(g->sub[i], loc, s, ctx));
			for (int i = 0; i < (int) vs.size(); ++i) {
				const Value &v2 = vs[i];
				if (i == 0) {
					loadLVal(v2, "$t0");
				} else {
					loadLVal(v2, "$t1");
					TokenType tty = get<1>(((GLexeme *) g->sub[i * 2 - 1])->t);
					if (tty == EQL) program.emplace_back("seq $t0, $t0, $t1");
					else program.emplace_back("sne $t0, $t0, $t1");
				}
			}
			int id = newVar(), offset = s.alloc(4);
			valueTypeMap[id] = Stk;
			stkOffsetMap[id] = offset;
			tempVarSet.insert(id);
			Value v = {Stk, id};
			program.emplace_back(storeOnStack(offset, "$t0"));
			return v;
		}
	}

	Value GenLAndExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		if (g->sub.size() == 1) return GenEqExp(g->sub[0], loc, s, ctx);
		else {
			int id = newVar(), offset = s.alloc(4), shortLabel = newLabel();
			valueTypeMap[id] = Stk;
			stkOffsetMap[id] = offset;
			tempVarSet.insert(id);
			Value v = {Stk, id};
			for (int i = 0; i < (int) g->sub.size(); i += 2) {
				Value v2 = GenEqExp(g->sub[i], loc, s, ctx);
				if (i == 0) {
					loadLVal(v2, "$t0");
					program.emplace_back("sne $t0, $t0, $0");
					program.emplace_back(storeOnStack(offset, "$t0"));
					program.push_back("beqz $t0, l_" + to_string(shortLabel));
				} else {
					loadLVal(v, "$t0");
					loadLVal(v2, "$t1");
					program.emplace_back("sne $t1, $t1, $0");
					program.emplace_back("and $t0, $t0, $t1");
					program.emplace_back(storeOnStack(offset, "$t0"));
					program.push_back("beqz $t0, l_" + to_string(shortLabel));
				}
			}
			emitLabel(shortLabel);
			return v;
		}
	}

	Value GenLOrExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		if (g->sub.size() == 1) return GenLAndExp(g->sub[0], loc, s, ctx);
		else {
			int id = newVar(), offset = s.alloc(4), shortLabel = newLabel();
			valueTypeMap[id] = Stk;
			stkOffsetMap[id] = offset;
			tempVarSet.insert(id);
			Value v = {Stk, id};
			for (int i = 0; i < (int) g->sub.size(); i += 2) {
				Value v2 = GenLAndExp(g->sub[i], loc, s, ctx);
				if (i == 0) {
					loadLVal(v2, "$t0");
					program.emplace_back("sne $t0, $t0, $0");
					program.emplace_back(storeOnStack(offset, "$t0"));
					program.push_back("bnez $t0, l_" + to_string(shortLabel));
				} else {
					loadLVal(v, "$t0");
					loadLVal(v2, "$t1");
					program.emplace_back("sne $t1, $t1, $0");
					program.emplace_back("or $t0, $t0, $t1");
					program.emplace_back(storeOnStack(offset, "$t0"));
					program.push_back("bnez $t0, l_" + to_string(shortLabel));
				}
			}
			emitLabel(shortLabel);
			return v;
		}
	}

	ConstExpr EvalConstExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		return EvalAddExp((GAddExp *) g->sub[0], loc, s, ctx);
	}

	ConstExpr EvalExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		return EvalAddExp((GAddExp *) g->sub[0], loc, s, ctx);
	}

	ConstExpr EvalLVal(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		const Token &t = ((GLexeme *) g->sub[0])->t;
		auto pred = [] (GrammarElement *p) { return p->_type == Lexeme && get<1>(((GLexeme *) p)->t) == LBRACK; };
		auto dimCount = count_if(g->sub.begin(), g->sub.end(), pred);
		const auto &var = lookupVar(get<2>(t));
		assert(var.type - dimCount == Int);
		const Storage &sto = storageMap.find(var.id)->second;
		if (var.type == IntArrayArray)
			return sto.valVV
				[EvalExp((GExp *) g->sub[2], loc, s, ctx)]
				[EvalExp((GExp *) g->sub[5], loc, s, ctx)];
		else if (var.type == IntArray)
			return sto.valV[EvalExp((GExp *) g->sub[2], loc, s, ctx)];
		else return sto.val;
	}

	ConstExpr EvalPrimaryExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		if (g->sub[0]->_type == Lexeme) return EvalExp((GExp *) g->sub[1], loc, s, ctx);
		else if (g->sub[0]->_type == LVal) return EvalLVal((GLVal *) g->sub[0], loc, s, ctx);
		else return EvalNumber((GNumber *) g->sub[0], loc, s, ctx);
	}

	ConstExpr EvalNumber(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		return stoi(get<2>(((GLexeme *) g->sub[0])->t));
	}

	ConstExpr EvalUnaryExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		if (g->sub[0]->_type == PrimaryExp) return EvalPrimaryExp((GPrimaryExp *) g->sub[0], loc, s, ctx);
		else {
			int r = EvalUnaryExp((GUnaryExp *) g->sub[1], loc, s, ctx);
			return get<1>(((GLexeme *) g->sub[0]->sub[0])->t) == PLUS ? r : -r;
		}
	}

//	ConstExpr EvalUnaryOp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
//		return 0;
//	}

	ConstExpr EvalMulExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		ConstExpr r = 1;
		TokenType t = MULT;
		for (const auto &gg : g->sub) {
			if (gg->_type == UnaryExp) {
				if (t == MULT) r *= EvalUnaryExp((GUnaryExp *) gg, loc, s, ctx);
				else if (t == DIV) {
					int e = EvalUnaryExp((GUnaryExp *) gg, loc, s, ctx);
					if (e) r /= e;
					else panic("[Gen] division by zero in mul-exp");
				} else {
					int e = EvalUnaryExp((GUnaryExp *) gg, loc, s, ctx);
					if (e) r %= e;
					else panic("[Gen] modulo zero in mul-exp");
				}
			}
			else t = get<1>(((GLexeme *) gg)->t);
		}
		return r;
	}

	ConstExpr EvalAddExp(GrammarElement *g, set<Variable> &loc, Stack &s, const Context &ctx) {
		ConstExpr r = 0, sgn = 1;
		for (const auto &gg : g->sub) {
			if (gg->_type == MulExp) r = r + sgn * EvalMulExp((GMulExp *) gg, loc, s, ctx);
			else {
				const Token &t = ((GLexeme *) gg)->t;
				if (get<1>(t) == PLUS) sgn = 1;
				else sgn = -1;
			}
		}
		return r;
	}

	void fillStackSizes() {
		for (const auto &u : fillStackSizeTask) {
			char tmp[2333];
			sprintf(tmp, program[u.first].c_str(), stackSizes[u.second] + 4); // for $ra
			program[u.first] = string(tmp);
		}
	}
}
namespace Opt {
	using namespace std;
	using Gen::program;
	vector<string> ret;

	void OptLoadAfterStore () {
		ret.clear();
		swap(ret, program);
		const string *las = new string("");
		for (const auto &instr : ret) {
			if (las->length() > 2 && instr.length() > 2 &&
				las->substr(2) == instr.substr(2) &&
				las->substr(0, 2) == "sw" && instr.substr(0, 2) == "lw") {
				;
			} else {
				program.emplace_back(instr);
			}
			las = &instr;
		}
	}

	void OptRedundantStore() {
		// sw $t0, -56($sp)
		// 01234567

		ret.clear();
		swap(ret, program);

		set<string> loadedVar;
		for (const auto &instr : ret) {
			if (instr.length() > 2 && instr.substr(0, 2) == "lw") {
				loadedVar.insert(instr.substr(8));
			}
		}

		bool inCall = false;
		for (const auto &instr : ret) {
			if (instr.find("addiu $fp") != string::npos) {
				inCall = true;
			} else if (instr.find("jal f_") != string::npos) {
				inCall = false;
			}
			if (!inCall && instr.length() > 2 && instr.substr(0, 2) == "sw" && loadedVar.find(instr.substr(8)) == loadedVar.end()) {
				;
			} else program.emplace_back(instr);
		}
	}

	void OptDoubleReturn() {
		ret.clear();
		swap(ret, program);
		const string *las = new string("");
		for (const auto &instr : ret) {
			if (*las == "jr $ra" && instr == "jr $ra") {
				;
			} else {
				program.emplace_back(instr);
			}
			las = &instr;
		}
	}

	void Optimize() {
		OptLoadAfterStore();
//		OptRedundantStore();
		OptDoubleReturn();
	}
}
int main() {
	using namespace std;
	FILE *fIn = fopen("testfile.txt", "rb");
	FILE *fOut = fopen("output.txt", "wb");
	FILE *fGen = fopen("mips.txt", "wb");
	FILE *fErr = fopen("error.txt", "wb");
	int r;
	r = Lex::main(fIn);
	r = Gra::main(Lex::tokens);
	Err::traverse(Gra::AST);

	sort(ErrDefine::errors.begin(), ErrDefine::errors.end());
	for (auto u : ErrDefine::errors) {
#ifdef LOCAL_DEBUG
		printf("%d %c %s\n", u.first, tolower(u.second), ErrDefine::errorMessage[u.second].c_str());
#endif
		fprintf(fErr, "%d %c\n", u.first, tolower(u.second));
	}

	Gen::GenCompUnit(Gra::AST);

	Opt::Optimize();

	for (const auto &u : initializer_list<string> {
		".data"
	}) {
#ifdef LOCAL_DEBUG
		printf("%s\n", u.c_str());
#endif
		fprintf(fGen, "%s\n", u.c_str());
	}

	for (const auto &u : Gen::data) {
#ifdef LOCAL_DEBUG
		printf("%s\n", u.c_str());
#endif
		fprintf(fGen, "%s\n", u.c_str());
	}

	for (const auto &u : initializer_list<string> {
		".text",
		"jal f_main",
		"li $v0, 10",
		"syscall"
	}) {
#ifdef LOCAL_DEBUG
		printf("%s\n", u.c_str());
#endif
		fprintf(fGen, "%s\n", u.c_str());
	}

	for (const auto &u : Gen::program) {
#ifdef LOCAL_DEBUG
		printf("%s\n", u.c_str());
#endif
		fprintf(fGen, "%s\n", u.c_str());
	}

	return 0;
}