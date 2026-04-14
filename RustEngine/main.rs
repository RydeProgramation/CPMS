mod wrapper_test_2;

use wrapper_test_2::{encode, decode};

fn main() {

    let encoded = encode("Test");

    println!("Encoded size: {}", encoded.size);

    let decoded = decode(encoded);

    println!("Decoded text: {}", decoded);

}
