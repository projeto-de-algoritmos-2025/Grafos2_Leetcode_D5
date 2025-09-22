class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        contagem = collections.Counter(nums)
        heap = []
        
        for num, freq in contagem.items():
            if len(heap) < k:
                heapq.heappush(heap, (freq, num))
            elif freq > heap[0][0]:
                heapq.heapreplace(heap, (freq, num))
                
        resultado = [num for freq, num in heap]
        
        return resultado