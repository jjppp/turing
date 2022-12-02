#include <getopt.h>
#include <iostream>
#include <string>

using ArgResult = struct {
    std::string tm_filename;
    std::string input;
    bool        is_verbose;
};

static void print_help() {
    std::cerr
        << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>"
        << std::endl;
    std::exit(-1);
}

static ArgResult parse_args(int argc, char *argv[]) {
    static struct option long_options[] {
        {"verbose", no_argument, 0, 0},
            {"help", no_argument, 0, 0},
            {0, 0, 0, 0},
    };
    bool is_verbose   = false;
    int  option_index = 0;
    char ch           = -1;

    if (argc < 3) {
        print_help();
    }

    for (; true;) {
        ch = getopt_long(
            argc, argv,
            "hv",
            long_options,
            &option_index);
        if (ch == -1) {
            break;
        }
        switch (ch) {
            case 0: { // long options
                switch (long_options[option_index].name[0]) {
                    case 'v': {
                        is_verbose = true;
                        break;
                    }
                    case 'h':
                    default: print_help();
                }
                break;
            }
            case 'v': {
                is_verbose = true;
                break;
            }
            case 'h':
            default: print_help();
        }
    }
    if (argc - optind != 2) {
        print_help();
    }
    return {
        argv[optind],
        argv[optind + 1],
        is_verbose};
}

int main(int argc, char *argv[]) {
    auto arg_result = parse_args(argc, argv);
    return 0;
}