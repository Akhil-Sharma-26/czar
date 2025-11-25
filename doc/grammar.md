$$
\begin{align}
    [\text{prog}] &\to [\text{stmt}]^* 
\\
    [\text{stmt}] &\to
    \begin{cases}
        \text{return}(\text{expr}); 
    \\
        \text{maanlo}\space\text{ident} = [\text{expr}];
    \end{cases}

\\
    [\text{expr}] &\to 
    \begin{cases}
        \text{int\_lit}
    \\
        \text{ident}
    \end{cases}
\end{align}
$$