int *removeDuplicate(int *vector, int *dim)
{
    for (unsigned char i = 0; i < *dim; i++)
    {
        for (unsigned char j = i + 1; j < *dim; j++)
        {
            if (vector[i] == vector[j])
            {
                for (unsigned char k = j; k < *dim - 1; k++)
                {
                    vector[k] = vector[k + 1];
                }
                (*dim)--;

                j--;
            }
        }
    }

    return vector;
}

// -------------------------------------------------------------------------------------------------------
struct NodArb* stergeRad(struct NodArb* rad)
{
	struct NodArb* aux = rad;
	if (rad->left != NULL)
	{
		rad = aux->left;

		if (aux->right != NULL)
		{
			struct NodArb* maxS = aux->left;

			while (maxS->right != NULL)
				maxS = maxS->right;

			maxS->right = aux->right;
		}
	}
	else
		if (aux->right != NULL)
			rad = aux->right;
		else
			rad = NULL;

	free(aux->lib.denumire);
	free(aux);

	return rad;
}


struct NodArb* stergereNod(struct NodArb* rad, char* cheie)
{
	if (rad != NULL)
	{
		if (strcmp(cheie, rad->lib.denumire) == -1)
			rad->left = stergereNod(rad->left, cheie);
		else
			if (strcmp(cheie, rad->lib.denumire) == 1)
				rad->right = stergereNod(rad->right, cheie);
			else
				rad = stergeRad(rad);
		return rad;
	}
	else
		return NULL;
}



// -------------------------------------------------------------------------------------------------------
void calculBF(nodArb* rad)
{
	if (rad != NULL)
	{
		rad->BF = inaltimeArbore(rad->dreapta) - inaltimeArbore(rad->stanga);
		calculBF(rad->stanga);
		calculBF(rad->dreapta);
	}
}

nodArb* stergeDupaDenumire(nodArb* rad, char* denumire)
{
	if (rad != NULL)
	{
		if (strcmp(rad->info.denumire, denumire) == 0)
		{
			rad = stergeNodRecursiv(rad, rad->info.id);
			return rad;
		}
		else
		{
			rad->stanga = stergeDupaDenumire(rad->stanga, denumire);
			rad->dreapta = stergeDupaDenumire(rad->dreapta, denumire);
			return rad;
		}
	}
	else
		return NULL;
}


nodArb* rotatie_dreapta(nodArb* rad)
{
	printf("\nRotatie dreapta\n");
	nodArb* nod1 = rad->stanga;
	rad->stanga = nod1->dreapta;
	nod1->dreapta = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_stanga(nodArb* rad)
{
	printf("\nRotatie stanga\n");
	nodArb* nod1 = rad->dreapta;
	rad->dreapta = nod1->stanga;
	nod1->stanga = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_dreapta_stanga(nodArb* rad)
{
	printf("\nRotatie dreapta-stanga\n");
	nodArb* nod1 = rad->dreapta;
	nodArb* nod2 = nod1->stanga;
	nod1->stanga = nod2->dreapta;
	nod2->dreapta = nod1;
	rad->dreapta = nod2->stanga;
	nod2->stanga = rad;
	rad = nod2;
	return rad;
}

nodArb* rotatie_stanga_dreapta(nodArb* rad)
{
	printf("\nRotatie stanga-dreapta\n");
	nodArb* nod1 = rad->stanga;
	nodArb* nod2 = nod1->dreapta;
	nod1->dreapta = nod2->stanga;
	nod2->stanga = nod1;
	rad->stanga = nod2->dreapta;
	nod2->dreapta = rad;
	rad = nod2;
	return rad;
}

nodArb* reechilibrare(nodArb* rad)
{
	calculBF(rad);
	nodArb* stanga = rad->stanga;
	nodArb* dreapta = rad->dreapta;
	if (rad->BF <= -2 && stanga->BF <= -1)
	{
		rad = rotatie_dreapta(rad);
		calculBF(rad);
	}
	else
		if (rad->BF <= -2 && stanga->BF >= 1)
		{
			rad = rotatie_stanga_dreapta(rad);
			calculBF(rad);
		}
		else
			if (rad->BF >= 2 && dreapta->BF >= 1)
			{
				rad = rotatie_stanga(rad);
				calculBF(rad);
			}
			else
				if (rad->BF >= 2 && dreapta->BF <= -1)
				{
					rad = rotatie_dreapta_stanga(rad);
					calculBF(rad);
				}
	return rad;
}
