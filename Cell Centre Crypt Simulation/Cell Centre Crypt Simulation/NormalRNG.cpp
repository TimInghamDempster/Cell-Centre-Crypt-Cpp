struct NormalDistributionRNG
{
	double m_mean;
	double m_sd;

	bool m_hasSecondOfPair;
	double m_secondOfPair;

	NormalDistributionRNG(double mean, double sd)
	{
		m_mean = mean;
		m_sd = sd;
		m_hasSecondOfPair = false;
	}

	double Next()
	{
		if (m_hasSecondOfPair)
		{
			m_hasSecondOfPair = false;
			return m_secondOfPair;
		}
		else
		{
			m_hasSecondOfPair = true;

			double u;
			double v;
			double s;
			bool suitableUV = false;

			do
			{
				u = ((double)rand() / RAND_MAX * 2.0) - 1.0;
				v = ((double)rand() / RAND_MAX * 2.0) - 1.0;

				s = u * u + v * v;

				suitableUV = (s != 0.0) && (s < 1.0);
			} while (suitableUV == false);

			double factor = -2.0 * log(s) / s;
			factor = sqrt(factor);

			m_secondOfPair = v * factor * m_sd + m_mean;
			return u * factor * m_sd + m_mean;
		}
	}
};