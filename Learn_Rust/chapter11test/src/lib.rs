#[cfg(test)]
mod tests {
    use crate::shape::Rectangle;

    use  super::*;

    
    #[test]
    fn exploration() {
        let result = 2 + 2;
        assert_eq!(result, 4);
    }

    #[test]
    fn another(){
        panic!("Make this test fail");
    }

    #[test]
    fn larger_can_hold_smaller(){
        let larger = shape::Rectangle{length:8,width:7};
        let smaller = Rectangle{length:5,width:1};
        assert!(larger.can_hold(&smaller));
    }

    #[test]
    fn smaller_cannot_hold_larger() {
        let larger = Rectangle { length: 8, width: 7 };
        let smaller = Rectangle { length: 5, width: 1 };
        assert!(!smaller.can_hold(&larger));
    }

    #[test]
    fn it_adds_two() {
        assert_eq!(4, add_two(2));
    }

    #[test]
    fn greeting_contains_name() {
        let result = greeting("Carol");
        assert!(
            result.contains("Carol"),
            "Greeting did not contain name, value was `{}`", result
        );
    }

    #[test]
    #[should_panic(expected = "Guess value must be less than or equal to 100")]
    fn greater_than_100() {
        Guess::new(200);
    }

    #[test]
    fn it_works() -> Result<(), String> {
        if 2 + 2 == 4 {
            Ok(())
        } else {
            Err(String::from("two plus two does not equal four"))
        }
    }

    #[test]
    fn this_test_will_pass() {
        let value = prints_and_returns_10(4);
        assert_eq!(10, value);
    }

    #[test]
    fn this_test_will_fail() {
        let value = prints_and_returns_10(8);
        assert_eq!(5, value);
    }

    #[test]
    fn internal() {
        assert_eq!(4, internal_adder(2, 2));
    }
}
pub fn add_two(a: i32) -> i32 { a+ 2
}

pub fn greeting(name: &str) -> String {
    format!("Hello {}!", name)
}

fn prints_and_returns_10(a: i32) -> i32 {
    println!("I got the value {}", a);
    10
}



pub fn add_four(a: i32) -> i32 {
    internal_adder(a, 4)
}

//通过私有规则的设计，允许测试私有函数
fn internal_adder(a: i32, b: i32) -> i32 { a+ b
}
pub struct Guess {
    value: u32,
}
impl Guess {
    pub fn new(value: u32) -> Guess {
        if value < 1 || value > 100 {
            panic!("Guess value must be between 1 and 100, got {}.", value);
}
Guess { value
} }
}
 mod shape{
    pub struct Rectangle{
       pub length:u32,
       pub  width:u32,
    }

    impl Rectangle {
        pub fn can_hold(&self,other:&Rectangle)->bool{
            return self.length>other.length && self.width > other.width;
        }
    }
}