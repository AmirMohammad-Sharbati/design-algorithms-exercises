def generate_non_descendant_sequnece (length, bound):
    if(length == 1):
        base_sequence = list(list())
        for i in range(bound):
            base_sequence.append({i+1})
        return base_sequence

    prev_sequnces = generate_non_descendant_sequnece(length-1, bound)
    final_sequences = list(list())

    for sequence in prev_sequnces:
        for i in range(sequence[-1], bound+1):
            new_sequence = prev_sequnces
            new_sequence.append(i)
            final_sequences.append(new_sequence)
    return final_sequences


n, m, q = int(input().split(" "))

constraints = list(list())
for i in range(q):
    a, b, c, d = int(input().split(" "))
    constraints.append({a, b, c, d})
    
all_non_descentant_sequences = generate_non_descendant_sequnece(n, m)

max_value = 0
for sequence in all_non_descentant_sequences:
    value = 0
    for q in constraints:
        if (sequence[q[1]] - sequence[q[2]] == q[3]):
            value += q[4]
    if (max_value < value): max_value = value
    
print(max_value)
    
