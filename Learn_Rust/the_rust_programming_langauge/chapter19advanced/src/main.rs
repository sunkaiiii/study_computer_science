static mut COUNTER:u32 = 0;

fn main() {
    let mut num = 5;
    
    //创建裸指针
    let r1 = &num as *const i32;
    let r2 = &mut num as *mut i32;

    let address = 0x12345usize;
    let r = address as *const i32;

    //通过unsafe解引用
    unsafe{
        println!("r1 is: {}",*r1);
        println!("r2 is: {}", *r2);
    }

    //调用不安全函数
    unsafe{
        dangerous();
    }

    add_to_count(2);
    //访问可变静态变量也是不安全的
    unsafe{
        println!("COUNTER: {}",COUNTER);
    }

    let p1 = Point { x: 1, y: 0 };
    let p2 = Point { x: 2, y: 3 };
    let p3 = Point { x: 3, y: 3 };
    assert_eq!(p1+p2,p3);
    println!("{}",p3);
    
    let m1 = Millimeters(100);
    let m2 = Meters(2);
    println!("{}",(m1+m2).0);

    //传递函数
    let answer = do_twice(add_one, 5);
    println!("The answer is: {}",answer);

    //元组的创建也可以传递函数
    let list_of_status:Vec<Status> = (0u32..20).map(Status::Value).collect();

    let add = returns_closure();
    println!("{}",add.as_ref()(1)); 

}

unsafe fn dangerous(){}

fn add_to_count(inc:u32){
    //修改静态变量是不安全的
    unsafe{
        COUNTER+=inc;
    }
}

//运算符重载
use std::ops::Add;
#[derive(Debug,PartialEq)]
struct Point {
    x: i32,
    y: i32, 
}

impl Add for Point{
    type Output = Point;

    fn add(self, rhs: Self) -> Self::Output {
        Point{
            x:self.x+rhs.x,
            y:self.y+rhs.y,
        }
    }
}

//不使用默认类型
struct Millimeters(u32);
struct Meters(u32);
impl Add<Meters> for Millimeters {
    type Output = Millimeters;

    fn add(self, rhs: Meters) -> Self::Output {
        Millimeters(self.0+(rhs.0*1000))
    }
}


//用于在trait中附带另外一个trait功能的超trait
use std::fmt;

trait OutlinePrint: fmt::Display{
    fn outline_print(&self){
        let output = self.to_string();
        let len = output.len();
        println!("{}", "*".repeat(len + 4));
        println!("*{}*", " ".repeat(len + 2));
        println!("* {} *", output);
        println!("*{}*", " ".repeat(len + 2));
        println!("{}", "*".repeat(len + 4));
    }
}

impl OutlinePrint for Point {}

impl fmt::Display for Point {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "({}, {})", self.x, self.y)
    }
}


//传递函数
fn add_one(x: i32) -> i32 { 
    x+ 1
}
fn do_twice(f: fn(i32) -> i32, arg: i32) -> i32 {
    f(arg) + f(arg)
}


enum Status {
    Value(u32),
    Stop,
}


//通过trait对象返回闭包
fn returns_closure() -> Box<dyn Fn(i32)->i32>{
    return Box::new(|x| x+1);
}

