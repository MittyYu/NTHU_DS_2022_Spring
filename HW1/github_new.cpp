

const string SG = "Shotgun shells";
const string P = "Penetration bullets";
const string SB = "Super bullets";


template <class T>
void BaseQueue<T>::push(const T& item) {
    // resize
    if (size() >= _capacity) {
        int newCapacity = _capacity * 2;
        T* newQueue = new T[newCapacity];
        int Size = size(), index = _front + 1;
        for (int i = 0; i < Size; i++) {
            newQueue[i] = _queue[index];
            index = index == _capacity ? 0 : index + 1;
        }

        delete[] _queue;
        _queue = newQueue;
        _capacity = newCapacity;
    }

    if ((_rear + 1) % _capacity != _front) {
        _rear = (_rear + 1) % _capacity;
        _queue[_rear] = item;
    }
}

template <class T>
void BaseQueue<T>::pop() {
    if (!empty())
        _front = (_front + 1) % _capacity;
}



/* Core Functions */

BaseStack<char> *stage;
BaseQueue<string> specials;

void InitialzeStage(int W, int H) {
    stage = new BaseStack<char>[W];

    char input;
    for (int row = 0; row < H; row++) {
        for (int col = 0; col < W; col++) {
            cin >> input;
            stage[col].push(input);
        }
    }

    // pop ending zeros
    for (int i = 0; i < W; i++) {
        while (!stage[i].empty() && stage[i].top() == '_')
            stage[i].pop();
    }
}

int findMaxLevel(int left, int right) {
    // find max level within index [left, right]
    // used by genEnemy and ShowRes
    int ret = 0;
    for (int i = left; i <= right; i++)
        ret = max(ret, stage[i].size());
    return ret;
}

void generateEnemies(int col, int W) {
    int left = (col - 2 >= 0) ? col - 2 : 0;
    int right = (col + 2 < W) ? col + 2 : W - 1;
    int maxLevel = findMaxLevel(left, right);

    for (int i = left; i <= right; i++) {
        while (stage[i].size() < maxLevel)
            stage[i].push('_');
        stage[i].push('1');
        stage[i].push('1');
        stage[i].push('1');
    }
}

void ShootNormal(int col, int W) {
    if (col >= W || col < 0 || stage[col].empty())
        return;

    char ch = stage[col].top();
    stage[col].pop();

    // pop ending zeros
    while (!stage[col].empty() && stage[col].top() == '_')
        stage[col].pop();
    
    switch (ch) {
        case '2': specials.push(SG); break;
        case '3': specials.push(P); break;
        case '4': specials.push(SB); break;
        case '5': generateEnemies(col, W); break;
        default: break;
    }
}

void ShootSpecial(int col, int W) {
    if (col < 0 || col >= W || specials.empty())
        return;
        
    string bullet = specials.front();
    specials.pop();
    
    if (bullet == SG) {
        int left = (col - 2 >= 0) ? col - 2 : 0;
        int right = (col + 2 < W) ? col + 2 : W - 1;
        for (int i = left; i <= right; i++)
            ShootNormal(i, W);
    } else if (bullet == P) {
        int cnt = 0;
        while (cnt < 3) {
            ShootNormal(col, W);
            cnt++;
        }
    } else if (bullet == SB) {
        char type = stage[col].top();
        while (!stage[col].empty() && stage[col].top() == type)
            ShootNormal(col, W);
    }
}

void FrontRow(int W) {
    int maxLevel = findMaxLevel(0, W - 1);
    cout << "FRONT_ROW, LEVEL:" << maxLevel << '\n';
    if (maxLevel) {
        for (int i = 0; i < W; i++) {
            if (stage[i].size() == maxLevel)
                cout << stage[i].top();
            else
                cout << '_';
            if (i != W - 1)
                cout << ' ';
        }
        cout << '\n';
    }
}

void ShowResult(int W) {
    cout << "END_RESULT:\n";

    int maxLevel = findMaxLevel(0, W - 1);
    if (maxLevel) {
        BaseStack<char> *revStage = new BaseStack<char>[W];
        for (int i = 0; i < W; i++) {
            while (!stage[i].empty()) {
                revStage[i].push(stage[i].top());
                stage[i].pop();
            }
        }
        
        for (int level = 1; level <= maxLevel; level++) {
            for (int i = 0; i < W; i++) {
                char ch = !revStage[i].empty() ? revStage[i].top() : '_';
                revStage[i].pop();
                cout << ch;
                if (i != W - 1)
                    cout << ' ';
            }
            cout << '\n';
        }

        delete[] revStage;
    }
}

void deleteStage() { delete[] stage; }