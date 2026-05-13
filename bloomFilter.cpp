#include <bits/stdc++.h>
using namespace std;

#if defined(_APPLE_)
    #include <mach/mach.h>
#elif defined(_linux_)
    #include <unistd.h>
#endif

size_t getMemoryUsage() {
#if defined(_linux_)
    FILE* f = fopen("/proc/self/statm", "r");
    if (!f) return 0;
    long rss;
    fscanf(f, "%*s %ld", &rss);
    fclose(f);
    return (size_t)rss * (size_t)sysconf(_SC_PAGESIZE);

#elif defined(_APPLE_)
    struct mach_task_basic_info info;
    mach_msg_type_number_t count = MACH_TASK_BASIC_INFO_COUNT;

    if (task_info(mach_task_self(),
                  MACH_TASK_BASIC_INFO,
                  (task_info_t)&info,
                  &count) != KERN_SUCCESS)
        return 0;

    return (size_t)info.resident_size;

#else
    return 0;
#endif
}

string genStr(int L = 10) {
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string s;
    s.reserve(L);
    for (int i = 0; i < L; i++)
        s.push_back(charset[rand() % (sizeof(charset)-1)]);
    return s;
}

struct BloomFilter {
    vector<bool> bit;
    int m;
    int k;

    BloomFilter(int m_bits = 10000000, int k_hash = 7) {
        m = m_bits;
        k = k_hash;
        bit.assign(m, false);
    }

    size_t hashCombine(const string &s, int seed) {
        size_t h = seed;
        for (char c : s) h = h * 131 + c;
        return h % m;
    }

    void insert(const string &s) {
        for (int i = 0; i < k; i++)
            bit[hashCombine(s, i + 1)] = true;
    }

    bool find(const string &s) {
        for (int i = 0; i < k; i++)
            if (!bit[hashCombine(s, i + 1)]) return false;
        return true;
    }
};

map<string, int> mp;          // ORDERED MAP
vector<string> storedKeys;
BloomFilter bloom(10000000, 7);

void insertKeysMap() {
    int N;
    cout << "Enter number of keys: ";
    cin >> N;

    storedKeys.reserve(N);
    srand(12345);

    size_t mem_before = getMemoryUsage();
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; i++) {
        string s = genStr();
        storedKeys.push_back(s);
        mp[s] = i;
    }

    auto end = chrono::high_resolution_clock::now();
    size_t mem_after = getMemoryUsage();

    cout << "\n[map] Insert time: "
         << chrono::duration<double>(end - start).count() << " sec\n";

    cout << "[map] Extra memory used: "
         << (mem_after - mem_before) / (1024.0 * 1024.0)
         << " MB\n";
}

void lookupHitsMap() {
    if (storedKeys.empty()) {
        cout << "Insert keys first.\n";
        return;
    }

    auto start = chrono::high_resolution_clock::now();
    long long sum = 0;
    for (auto &s : storedKeys)
        sum += mp[s];
    auto end = chrono::high_resolution_clock::now();

    cout << "[map] HIT lookup time: "
         << chrono::duration<double>(end - start).count()
         << " sec\n";
}

void lookupMissMap() {
    if (storedKeys.empty()) {
        cout << "Insert keys first.\n";
        return;
    }

    auto start = chrono::high_resolution_clock::now();
    int misses = 0;
    for (auto &s : storedKeys)
        if (mp.find("MISS_" + s) == mp.end()) misses++;
    auto end = chrono::high_resolution_clock::now();

    cout << "[map] MISS lookup time: "
         << chrono::duration<double>(end - start).count()
         << " sec\n";
}

void insertKeysBloom() {
    if (storedKeys.empty()) {
        cout << "Insert into map first.\n";
        return;
    }

    bloom = BloomFilter(10000000, 7);

    auto start = chrono::high_resolution_clock::now();
    for (auto &s : storedKeys)
        bloom.insert(s);
    auto end = chrono::high_resolution_clock::now();

    cout << "[Bloom] Insert time: " << chrono::duration<double>(end - start).count() << " sec\n";

    cout << "[Bloom] Memory used: " << bloom.bit.size() / (8.0 * 1024 * 1024) << " MB\n";
}

void lookupHitsBloom() {
    auto start = chrono::high_resolution_clock::now();
    int found = 0;
    for (auto &s : storedKeys)
        if (bloom.find(s)) found++;
    auto end = chrono::high_resolution_clock::now();

    cout << "[Bloom] HIT lookup time: " << chrono::duration<double>(end - start).count() << " sec\n";
}

void lookupMissBloom() {
    auto start = chrono::high_resolution_clock::now();
    int miss = 0;

    for (auto &s : storedKeys)
        if (!bloom.find("MISS_" + s)) miss++;

    auto end = chrono::high_resolution_clock::now();

    cout << "[Bloom] MISS lookup time: " << chrono::duration<double>(end - start).count() << " sec\n";
}

int main() {
    int choice;

    while (true) {
        cout << "\nBloom vs map\n";
        cout << "1. Insert keys into std::map\n";
        cout << "2. Lookup hits (map)\n";
        cout << "3. Lookup misses (map)\n";
        cout << "4. Insert keys into Bloom Filter\n";
        cout << "5. Lookup hits (Bloom)\n";
        cout << "6. Lookup misses (Bloom)\n";
        cout << "7. Show total memory usage\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: insertKeysMap(); break;
            case 2: lookupHitsMap(); break;
            case 3: lookupMissMap(); break;
            case 4: insertKeysBloom(); break;
            case 5: lookupHitsBloom(); break;
            case 6: lookupMissBloom(); break;
            case 7:
                cout << "RSS Memory: " << getMemoryUsage() / (1024.0 * 1024.0) << " MB\n";
                break;
            case 8: return 0;
            default: cout << "Invalid option.\n";
        }
    }
}