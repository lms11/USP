#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test, ...) do { char *message = test(__VA_ARGS__); tests_run++; if (message) return message; } while (0)
extern int tests_run;
