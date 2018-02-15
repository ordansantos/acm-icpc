std::array<int,5> foo {1,2,3,4,5};

// obtain a time-based seed:
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));

