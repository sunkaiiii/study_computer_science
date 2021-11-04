use std::{cell::RefCell, rc::Rc};
enum List {
    Cons(i32,Rc<List>),
    Nil,
}

use crate::List::{Cons,Nil};
use crate::List2::{Cons2,Nil2};

#[derive(Debug)]
enum List2 {
    Cons2(Rc<RefCell<i32>>,Rc<List2>),
    Nil2,
}

fn main() {
    // let list = Cons(1,Box::new(Cons(2,Box::new(Cons(3,Box::new(Nil))))));

    //引用计数，完成类似图的样式
    let a = Rc::new(Cons(5,Rc::new(Cons(10,Rc::new(Nil)))));
    let b = Cons(3,Rc::clone(&a));
    let c = Cons(4, Rc::clone(&a));
    println!("count after creating c={}",Rc::strong_count(&a));
    let x = 5;
    let y = MyBox::new(x);
    assert_eq!(5,x);
    assert_eq!(5,*y); //解引用

    //定义出拥有多个所有者 且能够进行修改的值
    let value = Rc::new(RefCell::new(5));
    let a = Rc::new(Cons2(Rc::clone(&value),Rc::new(Nil2)));
    let b = Cons2(Rc::new(RefCell::new(6)),Rc::clone(&a));
    let c = Cons2(Rc::new(RefCell::new(10)),Rc::clone(&a));
    *value.borrow_mut() += 10;
    println!("a after = {:?}", a);
    println!("b after = {:?}", b);
    println!("c after = {:?}", c);

    let c = CustomSmartPointer { data: String::from("my stuff") };
    let d = CustomSmartPointer { data: String::from("other stuff") };
    println!("CustomSmartPointers created."); 
    std::mem::drop(c); //手动执行drop,也可以忽略路径，直接调用drop
    //之后会执行drop 方法
}

use std::ops::Deref;

struct MyBox<T>(T);

impl <T> Deref for MyBox<T> {
    type Target = T;
    fn deref(&self)->&T{
        &self.0
    }
}

impl <T> MyBox<T> {
    fn new(x:T)->MyBox<T>{
        MyBox(x)
    }
}

struct CustomSmartPointer{
    data:String,
}

impl Drop for CustomSmartPointer {
    fn drop(&mut self) {
        println!("Dropping CustomSmartPointer with data '{}'",self.data);
    }
}
