#include <stdio.h>
int main (void)
{
	FILE *in, *out;
	struct pirate {
		char name[100]; /* real name */
		unsigned long pounds; /* in pounds sterling */
		unsigned int beard_len; /* in inches */
	} p, blackbeard = { "Edward Teach", 950, 48 };
	
	out = fopen ("pirate.data", "w");
	
	if (!out) {
		perror ("fopen");
		return 1;
	}

	if (!fwrite (&blackbeard, sizeof (struct pirate), 1, out)) {
		perror ("fwrite");
		return 1;
	}
	
	if (fclose (out)) {
		perror ("fclose");
		return 1;
	}
	
	in = fopen ("pirate.data", "r");
	if (!in) {
		perror ("fopen");
		return 1;
	}
	if (!fread (&p, sizeof (struct pirate), 1, in)) {
		perror ("fread");
		return 1;
	}
	if (fclose (in)) {
		perror ("fclose");
		return 1;
	}
	
	printf ("name=\"%s\" booty=%lu beard_len=%u\n",
			p.name, p.pounds, p.beard_len);
	return 0;
}
