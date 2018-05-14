#include <iostream>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <map>
#include <chrono>
#include <ratio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <getopt.h>
#include "mastermind.h"
#include "autosolve.h"

static void AutosolveAllCodes(const AutosolveConfig &autosolveConfig, bool showMetrics) {
    auto hist = std::map<int, int>();
    auto totalElapsed = std::chrono::duration<double, std::milli>();
    for (const auto &secret : AllCodes()) {
        std::vector<std::pair<Code, Score>> guesses;
        const auto start = std::chrono::high_resolution_clock::now();
        Autosolve(autosolveConfig, [&secret, &guesses](const auto &guess) {
            const auto score = EvaluateGuess(secret, guess);
            guesses.push_back(std::make_pair(guess, score));
            return score;
        });
        const auto stop = std::chrono::high_resolution_clock::now();
        totalElapsed += std::chrono::duration<double, std::milli>(stop - start);
        const auto numGuesses = guesses.size();
        std::cout << "secret: " << secret << " => #guesses: " << numGuesses << std::endl;
        ++hist[numGuesses];
    }
    for (const auto p : hist) {
        std::cout
                << std::fixed << std::setprecision(1) << std::setw(1) << p.first
                << " "
                << std::fixed << std::setprecision(1) << std::setw(4) << p.second
                << " "
                << std::string(static_cast<unsigned>(p.second / 12), '*')
                << std::endl;
    }
    if (showMetrics) {
        const auto averageElapsed = totalElapsed.count() / AllCodes().size();
        std::cout << std::endl;
        std::cout << "Average elapsed time: " << static_cast<int>(averageElapsed) << "ms" << std::endl;
    }
}

static void AutosolveRandomCode(const AutosolveConfig &autosolveConfig, bool showMetrics) {
    std::srand(static_cast<unsigned int>(time(nullptr)));
    const auto secret = GenerateSecret();
    std::vector<std::pair<Code, Score>> guesses;
    std::cout << "secret: " << secret << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();
    Autosolve(autosolveConfig, [&secret, &guesses](const auto &guess) {
        const auto score = EvaluateGuess(secret, guess);
        guesses.push_back(std::make_pair(guess, score));
        return score;
    });
    const auto stop = std::chrono::high_resolution_clock::now();
    std::cout << "Number of guesses: " << guesses.size() << std::endl;
    std::for_each(
            guesses.cbegin(),
            guesses.cend(),
            [](const auto &pair) {
                const auto &code = pair.first;
                const auto &score = pair.second;
                std::cout << "guess: " << code << " " << "score: " << score << std::endl;
            });
    if (showMetrics) {
        const auto elapsed = std::chrono::duration<double, std::milli>(stop - start);
        std::cout << "Elapsed time: " << static_cast<int>(elapsed.count()) << "ms" << std::endl;
    }
}

static void usage() {
    std::cerr << "Usage: mastermind [OPTION]" << std::endl;
    std::cerr << "  -a, --all                      " << "exhaustively autosolve all secrets" << std::endl;
    std::cerr << "  -p, --parallel                 " << "enable parallelism" << std::endl;
    std::cerr << "  -t, --num-threads=num          " << "number of threads to use when parallelism is enabled"
              << std::endl;
    std::cerr << "                                 " << "(default: std::thread::hardware_concurrency or 2)"
              << std::endl;
    std::cerr << "  -s, --set-size-threshold=num   " << "size of 'set' below which to ignore parallelism" << std::endl;
    std::cerr << "                                 " << "(default: 32)" << std::endl;
    std::cerr << "  -m, --metrics                  " << "show metrics" << std::endl;
    std::cerr << "  -v, --verbose                  " << "verbose output" << std::endl;
    std::cerr << "  -h, --help                     " << "display this usage information" << std::endl;
    exit(1);
}

static struct option longopts[] = {
        {"all",                no_argument,       nullptr, 'a'},
        {"parallel",           no_argument,       nullptr, 'p'},
        {"num-threads",        required_argument, nullptr, 't'},
        {"set-size-threshold", required_argument, nullptr, 's'},
        {"show-metrics",       no_argument,       nullptr, 'm'},
        {"verbose",            no_argument,       nullptr, 'v'},
        {"help",               no_argument,       nullptr, 'h'},
        {nullptr, 0,                              nullptr, 0}
};

int main(int argc, char *argv[]) {


    bool all = false;
    bool showMetrics = false;
    bool verbose = false;

    const auto hardwareConcurrency = std::thread::hardware_concurrency();
    const auto defaultConcurrency = hardwareConcurrency > 0 ? hardwareConcurrency : 2;
    auto autosolveConfig = AutosolveConfig(false, defaultConcurrency, 32);

    int ch;
    while ((ch = getopt_long(argc, argv, "apt:s:mvh", longopts, nullptr)) != -1) {
        switch (ch) {
            case 'a':
                all = true;
                break;
            case 'p':
                autosolveConfig.enableParallelism = true;
                break;
            case 't':
                autosolveConfig.numThreads = static_cast<int>(strtol(optarg, nullptr, 10));
                break;
            case 's':
                autosolveConfig.setSizeThreshold = static_cast<int>(strtol(optarg, nullptr, 10));
                break;
            case 'm':
                showMetrics = true;
                break;
            case 'v':
                verbose = true;
                break;
            case 'h':
            default:
                usage();
        }
    }

    if (verbose) {
        std::cout << "all: " << all << std::endl;
        std::cout << "enableParallelism: " << autosolveConfig.enableParallelism << std::endl;
        std::cout << "numThreads: " << autosolveConfig.numThreads << std::endl;
        std::cout << "setSizeThreshold: " << autosolveConfig.setSizeThreshold << std::endl;
        std::cout << "show metrics: " << showMetrics << std::endl;
    }

    if (all) {
        AutosolveAllCodes(autosolveConfig, showMetrics);
    } else {
        AutosolveRandomCode(autosolveConfig, showMetrics);
    }
}
