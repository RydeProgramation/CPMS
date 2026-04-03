use std::ffi::CString;
use std::os::raw::c_char;
use libloading::{Library, Symbol};

// ⚠️ Correspond exactement à ton struct C++
#[repr(C)]
struct Data {
    Size: u64,
}

// ⚠️ Signature correcte pour FFI : le dernier paramètre est un pointeur vers Data
type EncodeFn = unsafe extern "C" fn(input: *const c_char, size: usize, output_: *mut Data);

fn main() {
    // Charger la DLL
    let lib = unsafe { Library::new("SharedEngine.dll").expect("Impossible de charger la DLL") };

    unsafe {
        // Récupérer la fonction Encode
        let encode: Symbol<EncodeFn> = lib.get(b"Encode").expect("Impossible de trouver Encode");

        let text = "Hello World!";
        let c_text = CString::new(text).unwrap();
        let size = text.len();

        // Créer le struct Data qui recevra le résultat
        let mut data = Data { Size: 0 };

        // Appeler la fonction
        encode(c_text.as_ptr(), size, &mut data);

        // Afficher la taille renvoyée
        println!("Taille renvoyée par Encode: {}", data.Size);
    }
}