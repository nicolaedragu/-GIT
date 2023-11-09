#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
extern void *get_operations();

void print_simple(int index, sensor *Senzor)
{
	if (Senzor[index].sensor_type == 0)
	{
		tire_sensor pneu = *(tire_sensor *)Senzor[index].sensor_data;
		printf("Tire Sensor\n");
		printf("Pressure: %.2f\n", pneu.pressure);
		printf("Temperature: %.2f\n", pneu.temperature);
		printf("Wear Level: %d%%\n", pneu.wear_level);
		if (pneu.performace_score == 0)
			printf("Performance Score: Not Calculated\n");
		else
			printf("Performance Score: %d\n", pneu.performace_score);
	}
	else if (Senzor[index].sensor_type == 1)
	{
		power_management_unit engine = *(power_management_unit *)Senzor[index].sensor_data;
		printf("Power Management Unit\n");
		printf("Voltage: %.2f\n", engine.voltage);
		printf("Current: %.2f\n", engine.current);
		printf("Power Consumption: %.2f\n", engine.power_consumption);
		printf("Energy Regen: %d%%\n", engine.energy_regen);
		printf("Energy Storage: %d%%\n", engine.energy_storage);
	}
}

int main(int argc, char const *argv[])
{
	int numar_senzori, i, j, pm = 0, tr = 0, cindex;
	FILE *fp = fopen(argv[1], "rb");
	sensor *Senzori;
	fread(&numar_senzori, sizeof(int), 1, fp);
	// printf("numar senzori: %d\n", numar_senzori);
	Senzori = malloc((numar_senzori + 5) * sizeof(sensor));
	for (i = 0; i <= numar_senzori - 1; i++)
	{
		Senzori[i].sensor_data = NULL;
		fread(&Senzori[i].sensor_type, sizeof(enum sensor_type), 1, fp);
		if (Senzori[i].sensor_type == 0)
		{
			Senzori[i].sensor_data = (tire_sensor *)malloc(sizeof(tire_sensor));
			fread(Senzori[i].sensor_data, sizeof(tire_sensor), 1, fp);
			tr++;
		}
		else if (Senzori[i].sensor_type == 1)
		{
			Senzori[i].sensor_data = (power_management_unit *)malloc(sizeof(power_management_unit));
			fread(Senzori[i].sensor_data, sizeof(power_management_unit), 1, fp);
			pm++;
		}

		fread(&Senzori[i].nr_operations, sizeof(int), 1, fp);
		Senzori[i].operations_idxs = malloc(Senzori[i].nr_operations * sizeof(int));
		// fread(&Senzori[i].operations_idxs, sizeof(Senzori[i].operations_idxs), 1, fp);
		for (j = 0; j < Senzori[i].nr_operations; j++)
			fread(&Senzori[i].operations_idxs[j], sizeof(int), 1, fp);
	}

	sensor *NouSenzori = malloc((numar_senzori + 5) * sizeof(sensor));
	sensor *TempSenzori = malloc((tr + 5) * sizeof(sensor));
	int k1 = -1, k2 = -1;
	for (i = 0; i <= numar_senzori - 1; i++)
	{
		if (Senzori[i].sensor_type == 1) // e PMU
		{
			k1++;
			// NouSenzori[k1].sensor_data = (power_management_unit *)realloc(NouSenzori[k1].sensor_data, sizeof(power_management_unit));
			NouSenzori[k1] = Senzori[i];
			// NouSenzori[++k1] = Senzori[i];
		}
		else // e TIRE
		{
			k2++;
			// NouSenzori[k2].sensor_data = (tire_sensor *)realloc(NouSenzori[k2].sensor_data, sizeof(tire_sensor));
			TempSenzori[k2] = Senzori[i];
		}
	}
	for (i = 0; i <= k2; i++)
	{
		NouSenzori[++k1] = TempSenzori[i];
	}
	// Adauga la sfarist pentru NouSenzori TIRE de la TempSenzori
	// sensor *SenzorClear = (sensor *)malloc((k1 + 2) * sizeof(sensor));
	void *operatii[10];
	// get_operations(operatii);
	char comanda[50];
	char ix[10];
	int index, pi = 0, pf = 0, ok, cap;
	fgets(comanda, 50, stdin);
	comanda[strcspn(comanda, "\n")] = 0;
	// get_operations(operatii);
	// void (*func)();
	while (strcmp(comanda, "exit") != 0)
	{
		// s = primul cuvant din comanda
		char s[50];
		pi = 0;
		pf = 0;
		while ((comanda[pf] >= 'a') && (comanda[pf] <= 'z'))
			pf++;
		pf--;
		while (pi != (pf + 1))
		{
			s[pi] = comanda[pi];
			pi++;
		}
		s[pf + 1] = '\0';
		// index = cifra corespunzatoare Senzorului din comanda
		// if ((s[0] == 'p') || (s[0] == 'a'))
		strcpy(ix, comanda + pf + 2);
		pi = pf + 2;
		pf = pf + 2;
		while (comanda[pf] != '\0')
			pf++;
		pf--;
		// if (comanda[pi] == '-')
		// index = atoi(ix);
		// else
		index = atoi(ix);
		if (((index < 0) || (index > k1)) && ((s[0] == 'p') || (s[0] == 'a')))
			printf("Index not in range!\n");
		else
		{
			// for (j = 0; j < NouSenzori[index].nr_operations; j++)
			// printf ("op_idxs[%d] = %d\n",j,NouSenzori[index].operations_idxs[j]);
			if (strcmp(s, "print") == 0)
				print_simple(index, NouSenzori);
			else if (strcmp(s, "analyze") == 0)
			{
				get_operations(operatii);
				// printf("nr operatii: %d\n", NouSenzori[index].nr_operations);
				for (j = 0; j < NouSenzori[index].nr_operations; j++)
				{
					void (*func)() = (void (*)())operatii[NouSenzori[index].operations_idxs[j]];
					func(NouSenzori[index].sensor_data);
				}
			}
		}
		if (strcmp(s, "nr") == 0)
		{
			printf("numar senzori = %d, cap = %d\n", k1, cap);
			printf("pm = %d, tr = %d\n", pm, tr);
		}
		if (strcmp(s, "clear") == 0)
		{
			i = 0;
			cap = -1;
			while (i <= k1)
			{
				ok = 1;
				if (NouSenzori[i].sensor_type == 0)
				{
					tire_sensor tir = *(tire_sensor *)NouSenzori[i].sensor_data;
					if ((tir.pressure < 19) || (tir.pressure > 28))
						ok = 0;
					else if (ok == 1)
					{
						if ((tir.temperature < 0) || (tir.temperature > 120))
							ok = 0;
						else if ((tir.wear_level < 0) || (tir.wear_level > 100))
							ok = 0;
					}
				}
				else if (NouSenzori[i].sensor_type == 1)
				{
					power_management_unit pow = *(power_management_unit *)NouSenzori[i].sensor_data;
					if ((pow.voltage < 10) || (pow.voltage > 20))
						ok = 0;
					else if (ok == 1)
					{
						if ((pow.current < -100) || (pow.current > 100))
							ok = 0;
						else if ((pow.power_consumption < 0) || (pow.power_consumption > 1000))
							ok = 0;
						else if ((pow.energy_regen < 0) || (pow.energy_regen > 100))
							ok = 0;
						else if ((pow.energy_storage < 0) || (pow.energy_storage > 100))
							ok = 0;
					}
				}
				if (ok == 0) // trebuie sters NouSenzori[i], NouSenzori[k1] e ultimul element
				{
					for (cindex = i; cindex <= k1 - 1; cindex++)
					{
						NouSenzori[cindex] = NouSenzori[cindex + 1];
					}
					k1--;
					NouSenzori = realloc(NouSenzori, (k1 + 1) * sizeof(sensor));
					// SenzorClear = realloc(SenzorClear, lungime * sizeof(sensor));
					// printf("lungime = %d, i = %d|\t", lungime, i);
				}
				else
					i++;
			}
		}
		fgets(comanda, 50, stdin);
		comanda[strcspn(comanda, "\n")] = 0;
	}

	// free memorie
	for (i = 0; i <= numar_senzori - 1; i++)
	{
		free(Senzori[i].sensor_data);
		free(Senzori[i].operations_idxs);
	}
	free(Senzori);

	// /*
	for (i = 0; i <= k2 - 1; i++)
	{
		free(TempSenzori[i].sensor_data);
		free(TempSenzori[i].operations_idxs);
	}
	free(TempSenzori);
	// */

	for (i = 0; i <= k1 - 1; i++)
	{
		free(NouSenzori[i].sensor_data);
		free(NouSenzori[i].operations_idxs);
	}
	free(NouSenzori);

	fclose(fp);
	return 0;
}
