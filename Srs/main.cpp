#include <iostream>
using namespace std;

const int N = 3e5 + 10;
const double INF = 1e30 + 10;

template<typename K, typename V> class Map {
public :
    Map *root, *left, *right, *par;
    K key;
    V val;
    int depth;

    Map* create(K key) {
        Map* newnode = new Map;
        newnode -> key = key;
        newnode -> val = 0;
        newnode -> left = nullptr;
        newnode -> right = nullptr;
        newnode -> par = nullptr;
        newnode -> depth = 1;
        return newnode;
    }

    void right_rotation(Map* a) {
        Map* b = a -> left;
        a -> left = b -> right;
        if (b -> right != nullptr) 
            b -> right -> par = a;
        if (a -> par != nullptr && a -> par -> right == a) 
            a -> par -> right = b;
        else if (a -> par != nullptr && a -> par -> left == a) 
            a -> par -> left = b;
        b -> par = a->par;
        b -> right = a;
        a -> par = b;
    }

    void left_rotation(Map* a) {
        Map* b = a -> right;
        a -> right = b -> left;
        if (b -> left != nullptr) 
            b -> left -> par = a;
        if (a -> par != nullptr && a -> par -> left == a) 
            a -> par -> left = b;
        else if (a -> par != nullptr && a -> par -> right == a) 
            a -> par -> right = b;
        b -> par = a -> par;
        b -> left = a;
        a -> par = b;
    }

    void helper(Map* node) {
        if (depthf(node -> left) - depthf(node -> right) > 1) 
            if (depthf(node -> left -> left) > depthf(node -> left -> right)) {
                node -> depth = max(depthf(node -> right) + 1, depthf(node -> left -> right) + 1);
                node -> left -> depth = max(depthf(node -> left -> left) + 1, depthf(node) + 1);
                right_rotation(node);
            }
            else {
                node -> depth = max(depthf(node -> right) + 1, depthf(node -> left -> right -> right) + 1);
                node -> left -> depth = max(depthf(node -> left -> left) + 1, depthf(node -> left -> right -> left) + 1);
                node -> left -> right -> depth = max(depthf(node) + 1, depthf(node -> left) + 1);
                left_rotation(node -> left);
                right_rotation(node);
            }
        else if (depthf(node -> left) - depthf(node -> right) < -1) 
            if (depthf(node -> right -> right) > depthf(node -> right -> left)) {
                node -> depth = max(depthf(node -> left) + 1, depthf(node -> right -> left) + 1);
                node -> right -> depth = max(depthf(node -> right -> right) + 1, depthf(node) + 1);
                left_rotation(node);
            }
            else {
                node -> right -> depth = max(depthf(node -> right -> right) + 1, depthf(node -> right -> left -> right) + 1);
                node -> depth = max(depthf(node -> left) + 1, depthf(node -> right -> left -> left) + 1);
                node -> right -> left -> depth = max(depthf(node) + 1, depthf(node -> right) + 1);
                right_rotation(node -> right);
                left_rotation(node);
            }
    }

    void balance(Map* node) {
        while (node != root) {
            int d = node -> depth;
            node = node -> par;
            if (node -> depth < d + 1) 
                node -> depth = d + 1;
            if (node == root and depthf(node -> left) - depthf(node -> right) > 1) {
                if (depthf(node -> left -> left) > depthf(node -> left -> right)) 
                    root = node -> left;
                else
                    root = node -> left -> right;
                helper(node);
                break;
            }
            else if (node == root and depthf(node -> left) - depthf(node -> right) < -1) {
                if (depthf(node -> right -> right) > depthf(node -> right -> left)) 
                    root = node -> right;
                else 
                    root = node -> right -> left;
                helper(node);
                break;
            }
            helper(node);
        }
    }

    int depthf(Map* node) {
        if (node == nullptr) 
            return 0;
        return node -> depth;
    }

    Map* insert(K key) {
        Map* newnode = create(key);
        if (root == nullptr) {
            root = newnode;
            return root;
        }
        Map *temp = root, *prev = nullptr;
        while (temp != nullptr) {
            prev = temp;
            if (key < temp -> key) 
                temp = temp -> left;
            else if (key > temp -> key) 
                temp = temp -> right;
            else {
                free(newnode);
                return temp;
            }
        }
        if (key < prev -> key) 
            prev -> left = newnode;
        else 
            prev -> right = newnode;
        newnode -> par = prev;
        balance(newnode);
        return newnode;
    }

    V& operator[](K key) {
        return insert(key) -> val;
    }
};

struct Node {
    string max_person, min_person;
    double max_val, min_val;
};

class SegmentTree {
public :    
    Node seg[N << 2];

    void combine(int id, int lid, int rid) {
        if (seg[lid].max_val == INF) {
            seg[id].max_person = seg[rid].max_person;
            seg[id].max_val = seg[rid].max_val;
            seg[id].min_person = seg[rid].min_person;
            seg[id].min_val = seg[rid].min_val;
            return;
        }
        if (seg[rid].max_val == INF) {
            seg[id].max_person = seg[lid].max_person;
            seg[id].max_val = seg[lid].max_val;
            seg[id].min_person = seg[lid].min_person;
            seg[id].min_val = seg[lid].min_val;
            return;
        }
        if (seg[lid].max_val >= seg[rid].max_val) {
            seg[id].max_val = seg[lid].max_val;
            if (seg[lid].max_val == seg[rid].max_val) 
                seg[id].max_person = min(seg[lid].max_person, seg[rid].max_person);
            else 
                seg[id].max_person = seg[lid].max_person;
        }
        else 
            seg[id].max_val = seg[rid].max_val, seg[id].max_person = seg[rid].max_person;
        if (seg[lid].min_val <= seg[rid].min_val) {
            seg[id].min_val = seg[lid].min_val;
            if (seg[lid].min_val == seg[rid].min_val) 
                seg[id].min_person = min(seg[lid].min_person, seg[rid].min_person);
            else 
                seg[id].min_person = seg[lid].min_person;
        }
        else 
            seg[id].min_val = seg[rid].min_val, seg[id].min_person = seg[rid].min_person;
    }

    void build(int l = 0, int r = N, int id = 1) {
        if (l + 1 == r) {
            seg[id].max_person = seg[id].min_person = "";
            seg[id].max_val = seg[id].min_val = INF;
            return;
        }
        build(l, (l + r) >> 1, id << 1);
        build((l + r) >> 1, r, id << 1 | 1);
        combine(id, id << 1, id << 1 | 1);
    }

    void update(int ind, double val, string name, int l = 0, int r = N, int id = 1) {
        if (l + 1 == r) {
            seg[id].max_val = seg[id].min_val = val;
            seg[id].max_person = seg[id].min_person = name;
            return;
        }
        if (ind < ((l + r) >> 1)) 
            update(ind, val, name, l, (l + r) >> 1, id << 1);
        else 
            update(ind, val, name, (l + r) >> 1, r, id << 1 | 1);
        combine(id, id << 1, id << 1 | 1);
    }

    string get_max() {
        if (seg[1].max_val == INF or seg[1].max_val <= 0.0) 
            return "";
        return seg[1].max_person;
    }

    string get_min() {
        if (seg[1].min_val == INF or seg[1].min_val >= 0.0) 
            return "";
        return seg[1].min_person;
    }
};

SegmentTree total;
Map<string, int> ID;                         
Map<int, int> bede;                        
Map<int, int> bekha;                          
Map<int, double> mojodi;                         
Map<pair<int, int>, double> person;                

int main() {   
    ios_base::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    total.build();
    int q, cnt = 0;
    cin >> q;
    while (q--) {
        int t, p1, p2;
        double amount;
        string s1, s2, out;
        cin >> t;
        switch (t) {
            case 1:
                cin >> s1 >> s2 >> amount;
                amount *= 100;
                p1 = (ID[s1] == 0 ? (ID[s1] = ++cnt) : ID[s1]), p2 = (ID[s2] == 0 ? (ID[s2] = ++cnt) : ID[s2]);

                if (person[{p1, p2}] > 0) 
                    bekha[p1]--, bede[p2]--;
                else if (person[{p1, p2}] < 0) 
                    bekha[p2]--, bede[p1]--;

                person[{p1, p2}] += amount, person[{p2, p1}] -= amount;
                mojodi[p1] -= amount, mojodi[p2] += amount;
                total.update(p1 - 1, mojodi[p1], s1), total.update(p2 - 1, mojodi[p2], s2);

                if (person[{p1, p2}] > 0) 
                    bekha[p1]++, bede[p2]++;
                else if (person[{p1, p2}] < 0) 
                    bekha[p2]++, bede[p1]++;
                
            break;
            case 2:
                out = total.get_max();
                cout << (out == "" ? "-1" : out) << '\n';
            break;
            case 3:
                out = total.get_min();
                cout << (out == "" ? "-1" : out) << '\n';
            break;
            case 4:
                cin >> s1;
                p1 = (ID[s1] == 0 ? (ID[s1] = ++cnt) : ID[s1]);
                cout << bede[p1] << '\n';
            break;
            case 5:
                cin >> s1;
                p1 = (ID[s1] == 0 ? (ID[s1] = ++cnt) : ID[s1]);
                cout << bekha[p1] << '\n';
            break;
            case 6:
                cin >> s1 >> s2;
                p1 = (ID[s1] == 0 ? (ID[s1] = ++cnt) : ID[s1]), p2 = (ID[s2] == 0 ? (ID[s2] = ++cnt) : ID[s2]);
                cout.precision(2);
                cout << fixed << person[{p2, p1}] / 100.00 << '\n';
            break;
        }
    }
    return 0;
}
