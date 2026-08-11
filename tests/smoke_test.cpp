#include <cassert>
#include <string_view>

#include <n64decomp/version.hpp>

int main()
{
    static_assert(n64decomp::VERSION_MAJOR == 0);
    static_assert(n64decomp::VERSION_MINOR == 1);
    static_assert(n64decomp::VERSION_PATCH == 0);

    assert(n64decomp::VERSION == std::string_view{"0.1.0"});

    return 0;
}
