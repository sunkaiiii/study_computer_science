using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace CP11
{
    class Program
    {
        static void Main(string[] args)
        {
            //打印所有用户的查询
            var query = from user in SampleData.AllUsers select user;
            //这个查询等价于
            var query2 = SampleData.AllUsers.Select(user => user);
            foreach(var user in query)
            {
                Console.WriteLine(user);
            }

            //仅仅选择user对象名称的查询
            IEnumerable<string> query3 = from user in SampleData.AllUsers select user.Name;
            foreach(string name in query3)
            {
                Console.WriteLine(name);
            }
            //使用Cast和OfType来处理弱类型集合
            ArrayList list = new ArrayList { "First", "Second", "Third" };
            IEnumerable<string> strings = list.Cast<string>(); //使用cast强制类型转换
            foreach(string item in strings)
            {
                Console.WriteLine(item);
            }
            list = new ArrayList { 1, "not an int", 2, 3 };
            IEnumerable<int> ints = list.OfType<int>(); //使用oftype来转换
            foreach(int item in ints)
            {
                Console.WriteLine(item);
            }

            //使用显示类型的范围变量来自动的调用Cast
            list= new ArrayList { "First", "Second", "Third" };
            strings = from string entry in list select entry.Substring(0, 3);
            foreach(string start in strings)
            {
                Console.WriteLine(start);
            }

            //使用多个where子句地查询表达式
            User tim = SampleData.Users.TesterTim;
            var query4 = from defect in SampleData.AllDefects
                         where defect.Status != Status.Closed
                         where defect.AssignedTo == tim
                         select defect.Summary;
            foreach(var summary in query4)
            {
                Console.WriteLine(summary);
            }
            //按照缺陷严重度以及最后修改时间进行排序
            var query5 = from defect in SampleData.AllDefects
                     where defect.Status != Status.Closed
                     where defect.AssignedTo == tim
                     orderby defect.Severity descending, defect.LastModified
                     select defect;
            foreach(var defect in query5)
            {
                Console.WriteLine("{0}: {1} ({2:d})", defect.Severity, defect.Summary,defect.LastModified);
            }

            //不使用let子句，按照用户名称的长度来排序
            var qr = from user in SampleData.AllUsers
                     orderby user.Name.Length
                     select user.Name;
            foreach(var name in qr)
            {
                Console.WriteLine("{0}: {1}", name.Length, name);
            }
            //使用let表达式来消除冗余的计算
            var qr2 = from user in SampleData.AllUsers
                 let length = user.Name.Length
                 orderby length
                 select new { Name = user.Name, Length = length };
            foreach (var entry in qr2)
            {
                Console.WriteLine("{0}: {1}", entry.Length, entry);
            }
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            //根据项目把缺陷和通知订阅连接在一起
            var qr3 = from defect in SampleData.AllDefects
                      join subscription in SampleData.AllSubscriptions
                      on defect.Project equals subscription.Project
                      select new { defect.Summary, subscription.EmailAddress };
            foreach(var entry in qr3)
            {
                Console.WriteLine("{0}: {1}", entry.EmailAddress, entry.Summary);
            }
            //在连接的时候使用过滤，过滤需要在链接之前
            qr3 = from defect in SampleData.AllDefects
                  where defect.Status == Status.Closed
                  join subscription in SampleData.AllSubscriptions on defect.Project equals subscription.Project
                  select new { defect.Summary, subscription.EmailAddress };
            foreach (var entry in qr3)
            {
                Console.WriteLine("{0}: {1}", entry.EmailAddress, entry.Summary);
            }

            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            //使用分组连接把缺陷和订阅连接到一起
            var qr4 = from defect in SampleData.AllDefects
                      join subscription in SampleData.AllSubscriptions
                      on defect.Project equals subscription.Project
                      into groupedSubscriptions
                      select new { Defect = defect, Subscriptions = groupedSubscriptions };
            foreach(var entry in qr4)
            {
                Console.WriteLine(entry.Defect.Summary);
                foreach(var sub in entry.Subscriptions)
                {
                    Console.WriteLine("     {0}", sub.EmailAddress);
                }
            }
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            //计算5月份每天产生的缺陷数量
            var dates = new DateTimeRange(SampleData.Start, SampleData.End);
            var qr5 = from date in dates
                      join defect in SampleData.AllDefects
                      on date equals defect.Created.Date
                      into joined
                      select new { Date = date, Count = joined.Count() };
            foreach(var grouped in qr5)
            {
                Console.WriteLine("{0:d}: {1}", grouped.Date, grouped.Count);
            }

            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            //用户和项目的交叉连接
            var qr6 = from user in SampleData.AllUsers
                      from project in SampleData.AllProjects
                      select new { User = user, Project = project };
            foreach(var pair in qr6)
            {
                Console.WriteLine("{0}/{1}", pair.User, pair.Project.Name);
            }

            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            //右边依赖左边元素的交叉连接
            var qr7 = from left in Enumerable.Range(1, 4)
                      from right in Enumerable.Range(11, left)
                      select new { Left = left, Right = right };
            foreach(var pair in qr7)
            {
                Console.WriteLine("Left={0}; Right={1}", pair.Left, pair.Right);
            }

            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            //用分配者来分组缺陷——无比简单的投影
            var q = from defect in SampleData.AllDefects
                    where defect.AssignedTo != null
                    group defect by defect.AssignedTo;
            foreach(var entry in q)
            {
                Console.WriteLine(entry.Key.Name);
                foreach(var defect in entry)
                {
                    Console.WriteLine("    ({0})  {1}", defect.Severity, defect.Summary);
                }
                Console.WriteLine();
            }

            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            //使用查询延续
            //使用另外一个投影来延续分组结果
            var q2 = from defect in SampleData.AllDefects
                     where defect.AssignedTo != null
                     group defect by defect.AssignedTo into grouped
                     select new { Assginee = grouped.Key, Count = grouped.Count() };
            foreach(var entry in q2)
            {
                Console.WriteLine("{0}: {1}", entry.Assginee.Name, entry.Count);
            }
            Console.WriteLine();
            //在group和select子句之后的查询表达式延续
            q2 = from defect in SampleData.AllDefects
                 where defect.AssignedTo != null
                 group defect by defect.AssignedTo into grouped
                 select new { Assginee = grouped.Key, Count = grouped.Count() } into result
                 orderby result.Count descending
                 select result;
            foreach (var entry in q2)
            {
                Console.WriteLine("{0}: {1}", entry.Assginee.Name, entry.Count);
            }
        }
    }
}
