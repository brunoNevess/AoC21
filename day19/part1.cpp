#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int X_AXIS = 0;
const int Y_AXIS = 1;
const int Z_AXIS = 2;
typedef vector<vector<int>> vi;
typedef vector<vi> vvi;

typedef struct point { int x,y,z; } point;
typedef struct matrix { point a,b,c; } matrix;
matrix rotations; // rotations matrix
void invert(vector<vector<int>>& a, int axis){ // 6 possilites
    int n = a.size();
    for(int row = 0; row < n;row++){
       a[row][axis] *= -1;
    }
}
void genRotations(){
    vi axis ={X_AXIS,Y_AXIS,Z_AXIS};
    vvi axisperms;
    do {
        for(int a = 0 ; a < 3; a++){
            rotations.push_back(axis);
            invert(axis,a);
        }
    } while(next_permutation(begin(axis),end(axis)));
};

typedef struct scanner scanner;

struct scanner {
	point bs[32];		/* beacons */
	int nb;

	scanner *base;		/* aligned to this scanner */
	const matrix *perm;	/* ..with rotation..*/
	point pos;		/* ..and pos (in that frame) */
};

static scanner ss[33];
static int ns;

static int
cmp_v(point a, point b)
{
	return
	    a.x < b.x ? -1 : a.x > b.x ? 1 :
	    a.y < b.y ? -1 : a.y > b.y ? 1 : a.z - b.z;
}

static point
add_vv(point a, point b)
{
	point ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return ret;
}

static point
sub_vv(point a, point b)
{
	point ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return ret;
}

static point
mul_vm(point v, const matrix *m)
{
	point ret;
	ret.x = v.x * m->a.x + v.y * m->a.y + v.z * m->a.z;
	ret.y = v.x * m->b.x + v.y * m->b.y + v.z * m->b.z;
	ret.z = v.x * m->c.x + v.y * m->c.y + v.z * m->c.z;
	return ret;
}

static void
read_input(void)
{
	static char buf[50];
	int s=0;
	
	while(fgets(buf, sizeof(buf), stdin)) {
		if (sscanf(buf, "--- scanner %d", &s) == 1)
			;
		else if (sscanf(buf, "%d,%d,%d",
		    &ss[s].bs[ss[s].nb].x,
		    &ss[s].bs[ss[s].nb].y,
		    &ss[s].bs[ss[s].nb].z) == 3)
		    	ss[s].nb++;

		if (s >= ns) ns = s+1;

		assert(s < LEN(ss));
		assert(ss[s].nb < LEN(ss->bs));
	}
}

static int
test_alignment(scanner *s, scanner *base, const matrix *perm, point pos)
{
	int b0i,b1i, nmatch=0;
	point b0,b1;

	for (b0i=0; b0i < base->nb; b0i++) {
		for (b1i=0; b1i < s->nb; b1i++) {
			b0 = base->bs[b0i];

			b1 = s->bs[b1i];
			b1 = mul_vm(b1, perm);
			b1 = add_vv(b1, pos);

			if (cmp_v(b0, b1) == 0) {
				if (++nmatch >= 12)
					return 1;
				break;
			}
		}

		if (b0i - nmatch > base->nb - 12)
			return 0;
	}

	return 0;
}

static int
try_align(scanner *s, scanner *base)
{
	int pi, b0i,b1i;
	const matrix *perm;
	point pos;

	for (pi=0; pi < LEN(perms); pi++)
	for (b0i=0; b0i < base->nb; b0i++)
	for (b1i=0; b1i < s->nb; b1i++) {
		perm = &perms[pi];

		pos = s->bs[b1i];
		pos = mul_vm(pos, perm);
		pos = sub_vv(base->bs[b0i], pos);

		if (test_alignment(s, base, perm, pos)) {
			//printf("match %ld <- %ld perm=%ld "
			//    "pos=%d,%d,%d\n",
			//    base-ss, s-ss, perm-perms,
			//    pos.x,pos.y,pos.z);
			s->base = base;
			s->perm = perm;
			s->pos = pos;
			return 1;
		}
	}

	return 0;
}

static void
align_all(void)
{
	int dirty=1, i,j;

	while (dirty)
		for (dirty=i=0; i<ns; i++) {
			if (i && !ss[i].base)
				continue;
			for (j=1; j<ns; j++) {
				if (ss[j].base)
					continue;
				if (try_align(ss+j, ss+i))
					dirty = 1;
			}
		}
}

static int
count_beacons(void)
{
	static point bs[LEN(ss)*LEN(ss->bs)];
	int count=0, si,bi,i;
	scanner *s;
	point pos;

	for (si=0; si<ns; si++)
	for (bi=0; bi<ss[si].nb; bi++) {
		s = ss+si;
		pos = s->bs[bi];

		while (s->base) {
			pos = mul_vm(pos, s->perm);
			pos = add_vv(pos, s->pos);

			s = s->base;
		}

		for (i=0; i<count; i++)
			if (cmp_v(pos, bs[i]) == 0)
				break;

		if (i==count)
			bs[count++] = pos;
	}

	return count;
}

static int
max_dist(void)
{
	static point pos[LEN(ss)];
	scanner *s0, *s;
	int i,j, dist, best=0;

	for (i=0; i<ns; i++) {
		s0 = ss+i;
		pos[i] = s0->pos;

		for (s = s0->base; s && s->base; s = s->base) {
			pos[i] = mul_vm(pos[i], s->perm);
			pos[i] = add_vv(pos[i], s->pos);
		}
	}

	for (i=0; i<ns-1; i++)
	for (j=i+1; j<ns; j++) {
		dist = abs(pos[i].x - pos[j].x) +
		       abs(pos[i].y - pos[j].y) +
		       abs(pos[i].z - pos[j].z);
		if (dist > best)
			best = dist;
	}

	return best;
}

int main(){
    genRotations();
	read();
	align_all();

	cout << "Part1: " << count_beacons() << endl;
    cout << "Part2: " <<  max_dist() << endl;
	return 0;
}