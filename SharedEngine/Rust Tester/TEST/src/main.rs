mod wrapper_test_1;

use wrapper_test_1::{encode, decode};

fn main() {

    let encoded = encode("hello");

    println!("{:?}", encoded);

    let decoded = decode(&encoded);

    println!("{}", decoded);

}