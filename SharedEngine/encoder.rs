fn main() {
    const MAGIC: [u8; 2] = [0x4D, 0x53];
    const VERSION: u8 = 1;  
    const TYPE: u8 = 1;

    let mut text = String::new();
    std::io::stdin().read_line(&mut text).unwrap();
    let mut frame: Vec<u8> = Vec::new(); 

    frame.extend_from_slice(&MAGIC);
    frame.push(VERSION);
    frame.push(TYPE);
    frame.extend_from_slice(text.as_bytes());  // CORRIGÉ

    println!("{:?}", frame);  // CORRIGÉ
}