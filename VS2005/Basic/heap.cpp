class A
{
public:
	A( ){ i = 7; }
private:
	int i;
};

int main(int argc, char **argv)
{
	A *pA = new A[2];
	delete []pA;

	return 0;
}