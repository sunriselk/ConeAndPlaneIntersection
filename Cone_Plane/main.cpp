#include <iostream>
const double nThresh = 0.2;

int main()
{
	double gama, alpha;

	int nCount = 0;
	for (gama = 0; gama < 180; gama=gama+0.1)
	{
		for (alpha = 0; alpha < 360; alpha = alpha + 0.1)
		{
			double M1, M2, M3, M4;
			M1 = sin(gama) * cos(alpha);
			M2 = sin(gama) * sin(alpha);
			M3 = cos(gama);
			M4 = -100*(M1 + M2 + M3);

			if (M3 == 0)
				continue;

			double K1, K2, K3;
			K1 = -M1 / M3;
			K2 = -M2 / M3;
			K3 = -M4 / M3;

			double A, B, C, D, E;
			A = pow((1 - K1), 2) / pow(K3, 2);
			B = 2 * (K1 * K2 - K1 - K2) / pow(K3, 2);
			C = pow((1 - K2), 2) / pow(K3, 2);
			D = 2 * (K1 - 1) / K3;
			E = 2 * (K2 - 1) / K3;

			if (4 * A * C - B * B <= 0)
				continue;

			double Xc, Yc;
			Xc = (B * E - 2 * C * D) / (4 * A * C - B * B);
			Yc = (B * D - 2 * A * E) / (4 * A * C - B * B);

			double a2, b2;
			a2 = 2 * (A * Xc * Xc + C * Yc * Yc + B * Xc * Yc - 1) / (A + C + sqrt(pow(A - C, 2) + pow(B, 2)));
			b2 = 2 * (A * Xc * Xc + C * Yc * Yc + B * Xc * Yc - 1) / (A + C - sqrt(pow(A - C, 2) + pow(B, 2)));

			double Diff = abs(sqrt(a2) - sqrt(b2));

			double dCenter_diff = sqrt(pow(Xc - 100, 2) + pow(Yc - 100, 2));

			if (Diff < nThresh)
			{
				std::cout << "法向量为：[ " << M1 << ", " << M2 << ", " << M3 << " ]\t";
				std::cout << "圆心为：[ " << Xc << ", " << Yc << " ]\t";
				std::cout << "长轴：" << sqrt(a2) << "\t" << "短轴：" << sqrt(b2) << std::endl;
				nCount++;
			}

			if (gama == 0)
				break;
		}
	}
	std::cout << "\n设置阈值为" << nThresh << "时，找到的圆的个数为：" << nCount << std::endl;
	return 0;
}