package eval

import (
	"fmt"
	"math"
	"testing"
)

type Expr interface {
	//Eval 返回表达式env上文下文的值
	Eval(env Env) float64
	//静态检查
	Check(vars map[Var]bool) error
}

type Var string //表示一个变量，比如x

type literal float64 //表示一个数字常量，比如3.14

//unary表示一元操作符表达式,比如-x
type unary struct {
	op rune //'+','-'中的一个
	x  Expr
}

//binary 表示二元操作符表达式,比如x+y
type binary struct {
	op   rune //'+','-','*','/'
	x, y Expr
}

type call struct {
	fn   string //"pow","sin","sqrt" 中的一个
	args []Expr
}

//要对包含变量的表达式进行求值，需要一个上下文来把变量映射到数值
type Env map[Var]float64

func (v Var) Eval(env Env) float64 {
	return env[v]
}

func (l literal) Eval(_ Env) float64 {
	return float64(l) //对于常量，直接返回自己即可
}

func (u unary) Eval(env Env) float64 {
	switch u.op {
	case '+':
		return +u.x.Eval(env)
	case '-':
		return -u.x.Eval(env)
	}
	panic(fmt.Sprintf("unsupported unary operator: %q", u.op))
}

func (b binary) Eval(env Env) float64 {
	switch b.op {
	case '+':
		return b.x.Eval(env) + b.y.Eval(env)
	case '-':
		return b.x.Eval(env) - b.y.Eval(env)
	case '*':
		return b.x.Eval(env) - b.y.Eval(env)
	case '/':
		return b.x.Eval(env) / b.y.Eval(env)
	}
	panic(fmt.Sprintf("unsupported binary operator :%q", b.op))
}

func (c call) Eval(env Env) float64 {
	switch c.fn {
	case "pow":
		return math.Pow(c.args[0].Eval(env), c.args[1].Eval(env))
	case "sin":
		return math.Sin(c.args[0].Eval(env))
	case "sqrt":
		return math.Sqrt(c.args[0].Eval(env))
	}
	panic(fmt.Sprintf("unsupported function call: %s", c.fn))
}

//单元测试
func TestEval(t *testing.T) {
	tests := []struct {
		expr string
		env  Env
		want string
	}{
		{"sqrt(A/pi)", Env{"A": 87616, "pi": math.Pi}, "167"},
		{"pow(x,3)+pow(y,3)", Env{"x": 12, "y": 1}, "1729"},
		{"pow(x,3)+pow(y,3)", Env{"x": 9, "y": 10}, "1729"},
		{"5/9*(F-32)", Env{"F": -40}, "-40"},
		{"5/9*(F-32)", Env{"F": -32}, "0"},
		{"5/9*(F-32)", Env{"F": 212}, "100"},
	}
	var prevEcpr string
	for _, test := range tests {
		//仅仅在表达式变更的时候输出
		if test.expr != prevEcpr {
			fmt.Printf("\n%s\n", test.expr)
			prevEcpr = test.expr
		}
		expr, err := Parse(test.expr)
		if err != nil {
			t.Error(err)
			continue
		}
		got := fmt.Sprintf("%.6g", expr.Eval(test.env))
		fmt.Printf("\t%v=>%s\n", test.env, got)
		if got != test.want {
			t.Errorf("%s.Eval() in %v=%q,want %q\n", test.expr, test.env, got, test.want)
		}
	}
}
