#include <Halide.h>

int main(int argc, char **argv) {
    using namespace Halide;

    Func multiple;
    Var x;

    ImageParam input(type_of<uint8_t>(), 1);

    multiple(x) = input(x) * 2;

    std::vector<Argument> arg{input};

    Target target;

#ifdef TARGET_ARM32
    std::vector<Target::Feature> features;
    features.push_back(Target::ARM);
    target.set_features(features);
#elif TARGET_X86_64
#else
    target = get_target_from_environment();
#endif

    multiple.compile_to_file("twice_generate", arg, "twice", target);

    return 0;
}