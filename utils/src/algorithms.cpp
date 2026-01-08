#include <concepts>
#include <memory>

// Define the concept for the Mapper
template<typename F, typename Container, typename Value>
concept Mapper = requires(F f, const Container& c, size_t depth) {
    { f(c, depth) } -> std::convertible_to<Value>;
};

template<typename Container, std::totally_ordered Value, typename MapFunc>
requires Mapper<MapFunc, Container, Value>
struct KDTree {
public:
    KDTree(MapFunc mapper) : valueForDepth(std::move(mapper)) {}

private:
    struct Node {
        Container val;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
    };

    std::unique_ptr<Node> root;
    MapFunc valueForDepth;
};
