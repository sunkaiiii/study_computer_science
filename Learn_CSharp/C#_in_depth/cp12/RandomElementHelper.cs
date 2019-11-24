using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CP12
{
    static class RandomElementHelper
    {
        public static T RandomElement<T> (this IEnumerable<T> source, Random random)
        {
            if(source==null)
            {
                throw new ArgumentNullException("source");
            }
            if(random==null)
            {
                throw new ArgumentNullException("random");
            }
            ICollection collection = source as ICollection;
            if (collection != null)
            {
                int count = collection.Count;
                if(count==0)
                {
                    throw new InvalidOperationException("Sequence was empty.");
                }
                int index = random.Next(count);
                return source.ElementAt(index);
            }
            using IEnumerator<T> iterator = source.GetEnumerator();
            if (!iterator.MoveNext())
            {
                throw new InvalidOperationException("Sequence was empty.");
            }
            int countSoFar = 1;
            T current = iterator.Current;
            //我们有1/n的概率会用当前迭代器中的元素替 换已选出的随机元素，
            //n是已经迭代的元素数量。因此有1/2的概率会用第二个元素替换第一个， 
            //有1/3的概率用第三个元素替换前两个元素的结果，
            //以此类推。终的结果是，序列中每个元素 被选择的机会是均等的，而且我们只迭代了一次
            while (iterator.MoveNext())
            {
                countSoFar++;
                if (random.Next(countSoFar) == 0)
                {
                    current = iterator.Current;
                }
            }
            return current;
        }
    }
}
