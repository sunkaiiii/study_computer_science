use chapter10generic::aggregator::NewsArticle;
use chapter10generic::aggregator;
fn main() {
    let number_list = vec![34,50,25,100,65];

    let result = largest(&number_list);
    println!("The largest number is {}",result);

    let number_list = vec![102,34,6000,89,54,2,43,8];
    let result = largest(&number_list);
    println!("The largest number is {}",result);

    //生命周期
    let s1 = String::from("abcd");
    let s2 = "xyz";

    let result = longest(s1.as_str(), s2);
    println!("The longest string is {}",result);

    aggregator::longest_with_an_announcement(s1.as_str(), s2, "412");
}

fn largest<T:PartialOrd+Copy>(list:&[T])->T{
    let mut largest = list[0];

    for &item in list.iter(){
        if item>largest{
            largest = item;
        }
    }
    largest
}


//生命周期函数
//因为Rust并不能确定返回的引用会指向x还是指向 y。
//因此用生命周期标记来让让他们处于一个生命周期中
fn longest<'a>(x:&'a str,y:&'a str)->&'a str{
    if x.len()>y.len(){
        x
    }else{
        y
    }
}