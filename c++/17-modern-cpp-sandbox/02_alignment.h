#pragma once

struct Particle_1{
    double x, y, z; // 24 bytes
    int id;         // 4 bytes
    bool active;    // 1 byte
}; 

struct Particle_2{
    double x, y, z;          
    bool active;    
    int id;
}; 

struct Layout_1 {
    bool a;    
    double b;  
    bool c;    
    int d;    
};

struct Layout_2 {    
    double b;
    int d;  
    bool a;
    bool c;        
};

TEST(test_modern_cpp, test_alignment) {
    static_assert(sizeof(Particle_1) == 24 + 4 + 4);
    static_assert(sizeof(Particle_2) == 24 + 4 + 4);

    static_assert(sizeof(Layout_1) == 24); // 8 + 8 + 4 + 4
    static_assert(sizeof(Layout_2) == 16); // 8 + 4 + 1 + 1 + 2 padding for alignment
}
