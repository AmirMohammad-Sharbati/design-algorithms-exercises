def generate_non_descendant_sequence (length, bound):
    if(length == 1):
        base_sequence = [[i+1] for i in range(bound)]
        return base_sequence

    prev_sequences = generate_non_descendant_sequence(length-1, bound)
    final_sequences = []

    
    for sequence in prev_sequences: 
        for i in range(sequence[-1], bound+1): 
            final_sequences.append(sequence + [i])
    return final_sequences
    # return [sequence + [i] for sequence in prev_sequences for i in range(sequence[-1], bound+1)]


n, m, q = map(int, input().split(" "))
constraints = [list(map(int, input().split(" "))) for _ in range(q)]
    
all_non_descentant_sequences = generate_non_descendant_sequence(n, m)

max_value = 0
for sequence in all_non_descentant_sequences:
    value = 0
    for q in constraints:
        if (sequence[q[1]-1] - sequence[q[0]-1] == q[2]):
            value += q[3]
    if (max_value < value): max_value = value
    
print(max_value)