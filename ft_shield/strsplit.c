#include "main.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
    char	*c;
    size_t	i;

    if (s == NULL || start > strlen(s))
        return (NULL);
    if ((c = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
        return (NULL);
    i = 0;
    while (i < len && s[start] != '\0')
        c[i++] = s[start++];
    c[i] = '\0';
    return (c);
}

static	int		ft_countwords(char const *s, char c)
{
    int i;
    int split;

    i = 0;
    split = 0;
    while (*s)
    {
        if (split == 1 && *s == c)
            split = 0;
        if (split == 0 && *s != c)
        {
            split = 1;
            i++;
        }
        s++;
    }
    return (i);
}

static	int		ft_countchar(char const *s, char c)
{
    int i;

    i = 0;
    while (*s && *s++ != c)
        i++;
    return (i);
}

char			**ft_strsplit(char const *s, char c)
{
    int		i;
    int		nb_words;
    char	**tab;

    if (!c || s == NULL)
        return (NULL);
    nb_words = ft_countwords(s, c);
    tab = (char **)malloc(sizeof(*tab) * (nb_words + 1));
    if (tab == NULL)
        return (NULL);
    i = 0;
    while (nb_words--)
    {
        while (*s == c && *s)
            s++;
        tab[i] = ft_strsub((const char *)s, 0,
                           ft_countchar((const char *)s, c));
        if (tab[i++] == NULL)
            return (NULL);
        s = s + ft_countchar((const char *)s, c);
    }
    tab[i] = NULL;
    return (tab);
}