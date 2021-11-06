use std::thread;
use std::thread::spawn;
use std::time::Duration;
use std::sync::mpsc; //mpsc为multiple producer, single consumer的缩写
use std::sync::Mutex;
use std::sync::Arc;

fn main() {
    let v = vec![1,2,3];
    let handle = thread::spawn(move ||{ //使用move转移v的所有权
        println!("Here's a vector: {:?}",v);
    });

    for i in 1..5{
        println!("hi number {} from the main thread!",i);
        thread::sleep(Duration::from_millis(200));
    }
    handle.join().unwrap();

    //消息传递
    let (tx,rx) = mpsc::channel();
    thread::spawn(move | |{
        let vals = vec![
            String::from("hi"),
            String::from("from"),
            String::from("the"),
            String::from("thread"),
        ];
        for val in vals {
            tx.send(val).unwrap();
            thread::sleep(Duration::from_millis(200));
    }
    });
    for received in rx {
        println!("Got: {}", received);
    }

    //通过克隆发送者创建多个生产者
    let (tx,rx) = mpsc::channel();
    let tx1 = mpsc::Sender::clone(&tx);
    thread::spawn(move || {
        let vals = vec![
            String::from("hi"),
            String::from("from"),
            String::from("the"),
            String::from("thread"),
    ];
        for val in vals {
            tx1.send(val).unwrap();
            thread::sleep(Duration::from_millis(200));
    } });
    thread::spawn(move || {
        let vals = vec![
            String::from("more"),
            String::from("messages"),
            String::from("for"),
            String::from("you"),
    ];
        for val in vals {
            tx.send(val).unwrap();
            thread::sleep(Duration::from_millis(200));
    } });
    for received in rx {
        println!("Got: {}", received);
    }


    //互斥体
    let m = Mutex::new(5);
    {
        let mut num = m.lock().unwrap();
        *num = 6;
    }
    println!("m={:?}",m);

    //多个线程共享互斥体
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];
    for _ in 0..10{
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap();
            *num+=1;
        });
        handles.push(handle);
    }
    for handle in handles{
        handle.join().unwrap();
    }
    println!("Result: {}", *counter.lock().unwrap());
}
