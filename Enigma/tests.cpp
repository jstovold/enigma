//
//  tests.cpp
//  Enigma
//
//  Created by Petr Mánek on 20.02.14.
//  Copyright (c) 2014 TEEN, s.r.o. All rights reserved.
//

#include "tests.h"

void test_rotor() {
    // Encode the same letter few times over and
    // see if the rotor changes offset.
    
    rotor r(w1);
    
    std::cout << r.encode_forward(65);
    r.step();
    std::cout << r.encode_forward(65);
    r.step();
    std::cout << r.encode_forward(65);
    r.step();
    std::cout << r.encode_forward(65);
    r.step();
    
    std::cout << "\n";
}

void test_rotor_custom_wiring() {
    // Same as test_rotor, but with ordinary
    // alphabetic wiring.
    
    rotor r("ABCDEFGHIJKLMNOPQRSTUVWXYZ", { });
    
    std::cout << r.encode_forward(65);
    r.step();
    std::cout << r.encode_forward(65);
    r.step();
    std::cout << r.encode_forward(65);
    r.step();
    std::cout << r.encode_forward(65);
    r.step();
    
    std::cout << "\n";
}

void test_rotor_forward_backward() {
    // Encode letter forward and backward
    // to test symetric cipher.
    
    rotor r(w1);
    
    std::cout << r.encode_forward(65);
    std::cout << r.encode_backward(65);
    
    std::cout << "\n";
}

void test_rotor_turnover() {
    // Encode few letters and check for
    // the turnover position.
    
    rotor r(w1);
    r.set_offset(14);
    
    std::cout << r.encode_forward(65) << " - offset: " << r.get_offset() << " - turnover: " << r.is_in_turnover_position() << "\n";
    r.step();
    std::cout << r.encode_forward(65) << " - offset: " << r.get_offset() << " - turnover: " << r.is_in_turnover_position() << "\n";
    r.step();
    std::cout << r.encode_forward(65) << " - offset: " << r.get_offset() << " - turnover: " << r.is_in_turnover_position() << "\n";
    r.step();
    std::cout << r.encode_forward(65) << " - offset: " << r.get_offset() << " - turnover: " << r.is_in_turnover_position() << "\n";
    r.step();
    
    std::cout << "\n";
}

void test_machine_encode() {
    // Encode few letters and log the output.
    
    machine m;
    
    for (int i = 0; i < 100; i++) {
        std::cout << m.encode(65);
    }
    
    std::cout << "\n";
}

void test_plugboard() {
    // Set up simple plugboard config and
    // encode few letters, compare with
    // empty configuration.
    
    plugboard p;
    
    std::cout << "Without any plugs: ";
    for (char c = 'A'; c < 'G'; c++) {
        std::cout << p.encode(c);
    }
    std::cout << "\n\nWith A-B, C-D plugs: ";
    
    p.set('A', 'B');
    p.set('C', 'D');
    for (char c = 'A'; c < 'G'; c++) {
        std::cout << p.encode(c);
    }
    
    std::cout << "\n";
}

void test_machine_encode_plugboard() {
    // Encode few letters and log the output.
    
    machine m;
    
    m.rotors = std::vector<rotor>({ rotor(w1), rotor(w2), rotor(w3) });
    m.plugs.set('A', 'D');
    m.plugs.set('O', 'L');
    
    std::string s = m.encode_string("AHOJ");
    std::cout << "\n\nEntire encoded message: " << s;
    
    std::cout << "\n";
}

void test_machine_encode_decode() {
    // Encode few letters and log the output.
    
    machine m, n;
    
    m.rotors = std::vector<rotor>({ rotor(w1), rotor(w2), rotor(w3) });
    m.reflector = rotor(w_ra);
    m.plugs.set('A', 'D');
    m.plugs.set('O', 'L');
    
    n.rotors = std::vector<rotor>({ rotor(w1), rotor(w2), rotor(w3) });
    n.reflector = rotor(w_ra);
    n.plugs.set('A', 'D');
    n.plugs.set('O', 'L');
    
    for (int i = 0; i < 100; i++) {
        std::string s = m.encode_string("AHOJ");
        std::cout << "\nEntire encoded message: " << s;
        std::cout << "\nDecoding now...";
        
        std::string t = n.encode_string(s);
        std::cout << "\nEntire decoded message: " << t << "\n";
    }
    
    std::cout << "\n";
}
