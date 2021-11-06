use std::thread;
use std::time::Duration;

fn simulated_expensive_calculation(intensity:u32) -> u32{
    println!("calculating slowly...");
    thread::sleep(Duration::from_secs(2));
    intensity
}

struct Cacher<T> where T:Fn(u32)->u32{
    calculation:T,
    value:Option<u32>,
}

impl <T> Cacher<T> where T:Fn(u32) -> u32 {
    fn new(calculation:T) -> Cacher<T> {
        Cacher { calculation: calculation, value: None }
    }

    fn value(&mut self, arg:u32) -> u32{
        match self.value {
            Some(v)=>v,
            None=>{
                let v = (self.calculation)(arg);
                self.value = Some(v);
                v
            }
        }
    }
}

fn main() {
    let simulated_user_specified_value = 10;
    let simulated_random_number = 7;
    generate_workout(simulated_user_specified_value,simulated_random_number);

    //闭包捕捉变量
    let x = 4;
    let equal_to_x = |z| z==x;
    let y = 4;
    assert!(equal_to_x(y));

    //迭代器
    let v1 = vec![1,2,3];
    let v1_iter = v1.iter();
    for val in v1_iter{
        println!("Got: {}",val);
    }

    //生成其他迭代器的方法
    let v1: Vec<i32> = vec![1, 2, 3];
    let v2:Vec<_> = v1.iter().map(|x| x + 1).collect();
    assert_eq!(v2,vec![2,3,4]);  
    
    
}

fn generate_workout(intensity:u32,random_number:u32){
    let mut expensive_result = Cacher::new(|num|{
        println!("calculating slowly...");
        thread::sleep(Duration::from_secs(2));
        num
    });

    if intensity < 25{
        println!("Today, do {} pushups!", expensive_result.value(intensity));
        println!("Next, do {} situps!",expensive_result.value(intensity));
    }else{
        if random_number == 3{
            println!("Take a break today! Remember to stay hydrated!");
        }else{
            println!("Today, run for {} minutes!",expensive_result.value(intensity));
        }
    }
}
