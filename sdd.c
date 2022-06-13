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

// -------------------------------------------------------------------------------------------------------

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
