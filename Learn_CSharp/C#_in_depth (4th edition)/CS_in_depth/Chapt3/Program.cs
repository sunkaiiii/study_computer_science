using System;
using System.Collections.Generic;
using System.Linq.Expressions;

namespace Chapt3
{
    class Program
    {
        private string instanceField = "instance field";
        public Action<string> CreateAction(string methodParameter)
        {
            string methodLocal = "method local";
            string uncaptured = "uncaptured local";

            //Lambda捕获变量
            Action<string> action = lambdaParameter =>
            {
                string lambdaLocal = "lambda local";
                Console.WriteLine("Instance field: {0}", instanceField); Console.WriteLine("Method parameter: {0}", methodParameter);
                Console.WriteLine("Method local: {0}", methodLocal);
                Console.WriteLine("Lambda parameter: {0}", lambdaParameter);
                Console.WriteLine("Lambda local: {0}", lambdaLocal);
            };
            methodLocal = "modified method local";
            return action;
        }

        //从多个作用域捕获变量
        static List<Action> CreateCountingActions()
        {
            List<Action> actions = new List<Action>();
            int outerCounter = 0;
            for (int i = 0; i < 2; i++)
            {
                int innerCounter = 0;
                Action action = () =>
                {
                    Console.WriteLine("Outer: {0}; Inner: {1}", outerCounter, innerCounter);
                    outerCounter++;
                    innerCounter++;
                };
                actions.Add(action);
            }
            return actions;
        }
        static void Main(string[] args)
        {
            var demo = new Program();
            Action<string> action = demo.CreateAction("method argument");
            action("lambda argument");

            var actions = CreateCountingActions();
            actions[0]();
            actions[0]();
            actions[1]();
            actions[1]();

            //表达式树
            Expression<Func<int, int, int>> adder = (x, y) => x + y; 
            Console.WriteLine(adder);
            //表达式树可以构建委托
            Func<int, int, int> executableAdder = adder.Compile();
            Console.WriteLine(executableAdder(2, 3));
        }
    }
}
