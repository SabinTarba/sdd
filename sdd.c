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