package main

import (
	"fmt"
	"log"
	"net/http"

	"./eval"
	"./surface"
)

func parseAndCheck(s string) (eval.Expr, error) {
	if s == "" {
		return nil, fmt.Errorf("empty expression")
	}
	expr, err := eval.Parse(s)
	if err != nil {
		return nil, err
	}
	vars := make(map[eval.Var]bool)
	if err := expr.Check(vars); err != nil {
		return nil, err
	}
	for v := range vars {
		if v != "x" && v != "y" && v != "r" {
			return nil, fmt.Errorf("undefined variable:%s", v)
		}
	}
	return expr, nil
}

func main() {
	http.HandleFunc("/plot", surface.Plot)
	log.Fatal(http.ListenAndServe("localhost:8000", nil))
}
