use std::ffi::CString;
use std::os::raw::c_char;
use libloading::{Library, Symbol};

#[repr(C)]
struct Data {
    size: u64,
    ptr: *mut std::ffi::c_void,
}

type EncodeFn = unsafe extern "C" fn(input: *const c_char, size: usize) -> Data;
type FreeBufferFn = unsafe extern "C" fn(ptr: *mut std::ffi::c_void);

fn main() {
    let lib = unsafe { Library::new("SharedEngine.dll").expect("Impossible de charger la DLL") };

    unsafe {
        let encode: Symbol<EncodeFn> = lib.get(b"Encode").expect("Impossible de trouver Encode");

        let text = "Hello World!";
        let c_text = CString::new(text).unwrap();

        let mut data: Data = encode(c_text.as_ptr(), text.len());  // CHANGÉ: ajouté mut

        if !data.ptr.is_null() && data.size > 0 {
            let slice = std::slice::from_raw_parts(data.ptr as *const u8, data.size as usize);
            println!("Contenu encodé: {:?}", slice);
        }
        println!("Taille renvoyée par Encode: {}", data.size);

        // Libérer la mémoire allouée\
        let free_buffer: Symbol<FreeBufferFn> = lib.get(b"FreeBuffer").expect("Impossible de trouver FreeBuffer");
        
        free_buffer(data.ptr);
        
        // CHANGÉ: on remet le pointeur à null après libération
        data.ptr = std::ptr::null_mut();
        data.size = 0;

        let slice = std::slice::from_raw_parts(data.ptr as *const u8, data.size as usize);
        println!("Contenu encodé: {:?}", slice);
        println!("Taille renvoyée par Encode: {}", data.size);
    }
}