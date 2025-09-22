class Solution:
    def maxSpending(self, values: List[List[int]]) -> int:
        num_lojas = len(values)
        num_itens = len(values[0])
        heap = []

        for indice_loja in range(num_lojas):
            indice_item = num_itens - 1 
            heapq.heappush(heap, (values[indice_loja][indice_item], indice_loja, indice_item))

        total = 0
        dia = 1

        while heap:
            valor_item, loja, indice_item = heapq.heappop(heap)
            total += valor_item * dia
            dia += 1

            if indice_item > 0:
                proximo_indice = indice_item - 1
                heapq.heappush(heap, (values[loja][proximo_indice], loja, proximo_indice))

        return total
