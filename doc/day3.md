## adding variables

I'll be initially making the variable keyword to be "maano"/"let"

The grammar will change accordingly

I'll have List of statements and we execute them

My grammer for variable
```tex
[\text{prog}] &\to [\text{stmt}]^* 
\\
    [\text{stmt}] &\to
    \begin{cases}
        return(\text{expr}); 
    \\
        maanlo\space\text{ident} = [\text{expr}];
    \end{cases}
```


2. Now to generate code, we will be doing it for each AST node just as we parse each AST node!

3. visitor : match on a type. It will call the function matching the something!