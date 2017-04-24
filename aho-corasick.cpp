struct trie {
    map <char, trie*> children;
    char value;
    bool terminal;
    trie *parent;
    trie *failure;
    trie () : value('\0'), terminal(false){}
	~trie() {
		for (auto c: children)
			delete c.second;
	}
    void add (string &s, int i = 0){
        if (i != s.size()){
            if (!haschild(s[i])){
                children[s[i]] = new trie;
                children[s[i]]->value = s[i];
                children[s[i]]->parent = this;
            }
            children[s[i]]->add(s, i + 1);
        } else{
            terminal = true;
        }
    }
    bool isroot (){ return value == '\0'; }
    bool haschild(char c){ return children.count(c); }
};

void build_failure (trie *root){
    queue <trie*> q;
    for (auto &c: root->children){
        c.second->failure = root;
        for (auto &c2: c.second->children)
            q.push(c2.second);
    }
    while (!q.empty()){
        trie *node = q.front();
        q.pop();
        trie *f = node->parent->failure;
        while (!f->isroot() && !f->haschild(node->value))
            f = f->failure;
        if (f->haschild(node->value))
            f = f->children[node->value];
        node->failure = f;
        for (auto &c: node->children)
            q.push(c.second);
    }
}

/*
trie *atual = root;
for (int i = 0; i < s.size(); i++){
    while (!atual->isroot() && !atual->haschild(s[i])) atual = atual->failure;
    if (atual->haschild(s[i])) atual = atual->children[s[i]];
}
*/
