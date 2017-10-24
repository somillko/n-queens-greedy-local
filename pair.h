#ifndef PAIR_H
#define PAIR_H

struct Pair {
	/* Constructors */
	Pair () : r(0), c(0) {}
	Pair (int _r, int _c) : r(_r), c(_c) {}
	Pair (const Pair & p) : r(p.r), c(p.c) {}
	Pair (Pair* p) : r(p->r), c(p->c) {}

	/* Operator overloads */
	void operator= (const Pair & p);
	bool operator== (const Pair & rhs) const;
	bool operator!= (const Pair & rhs) const;

	/* Members */
	int r;
	int c;
};

#endif // !PAIR_H
