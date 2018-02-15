#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#pragma GCC diagnostic ignored "-Wunused-result"

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("avx,tune=native")

#pragma comment(linker, "/stack:20000000")
