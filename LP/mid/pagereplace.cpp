#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
using namespace std;

class PageReplacement {
private:
    vector<int> pages;
    int frameSize;
    
public:
    PageReplacement(vector<int> p, int f) : pages(p), frameSize(f) {}
    
    // FIFO Algorithm
    void fifo() {
        vector<int> frames;
        queue<int> pageQueue;
        int pageFaults = 0;
        
        cout << "\n=== FIFO Page Replacement ===\n";
        cout << "Page\tFrames\t\tPage Fault\n";
        cout << "-----------------------------------\n";
        
        for(int page : pages) {
            bool found = find(frames.begin(), frames.end(), page) != frames.end();
            
            if(!found) {
                pageFaults++;
                
                if(frames.size() < frameSize) {
                    frames.push_back(page);
                    pageQueue.push(page);
                } else {
                    int oldestPage = pageQueue.front();
                    pageQueue.pop();
                    
                    auto it = find(frames.begin(), frames.end(), oldestPage);
                    *it = page;
                    pageQueue.push(page);
                }
            }
            
            cout << page << "\t";
            for(int frame : frames) {
                cout << frame << " ";
            }
            cout << "\t\t" << (found ? "No" : "Yes") << "\n";
        }
        
        cout << "Total Page Faults: " << pageFaults << "\n";
    }
    
    // LRU Algorithm
    void lru() {
        vector<int> frames;
        int pageFaults = 0;
        
        cout << "\n=== LRU Page Replacement ===\n";
        cout << "Page\tFrames\t\tPage Fault\n";
        cout << "-----------------------------------\n";
        
        for(int page : pages) {
            auto it = find(frames.begin(), frames.end(), page);
            bool found = it != frames.end();
            
            if(found) {
                // Move to end (most recently used)
                frames.erase(it);
                frames.push_back(page);
            } else {
                pageFaults++;
                
                if(frames.size() < frameSize) {
                    frames.push_back(page);
                } else {
                    // Remove least recently used (first element)
                    frames.erase(frames.begin());
                    frames.push_back(page);
                }
            }
            
            cout << page << "\t";
            for(int frame : frames) {
                cout << frame << " ";
            }
            cout << "\t\t" << (found ? "No" : "Yes") << "\n";
        }
        
        cout << "Total Page Faults: " << pageFaults << "\n";
    }
    
    // Optimal Algorithm
    void optimal() {
        vector<int> frames;
        int pageFaults = 0;
        
        cout << "\n=== Optimal Page Replacement ===\n";
        cout << "Page\tFrames\t\tPage Fault\n";
        cout << "-----------------------------------\n";
        
        for(int i = 0; i < pages.size(); i++) {
            int page = pages[i];
            bool found = find(frames.begin(), frames.end(), page) != frames.end();
            
            if(!found) {
                pageFaults++;
                
                if(frames.size() < frameSize) {
                    frames.push_back(page);
                } else {
                    // Find page that will be used farthest in future
                    int farthest = -1;
                    int replaceIndex = 0;
                    
                    for(int j = 0; j < frames.size(); j++) {
                        int nextUse = pages.size();
                        
                        for(int k = i + 1; k < pages.size(); k++) {
                            if(pages[k] == frames[j]) {
                                nextUse = k;
                                break;
                            }
                        }
                        
                        if(nextUse > farthest) {
                            farthest = nextUse;
                            replaceIndex = j;
                        }
                    }
                    
                    frames[replaceIndex] = page;
                }
            }
            
            cout << page << "\t";
            for(int frame : frames) {
                cout << frame << " ";
            }
            cout << "\t\t" << (found ? "No" : "Yes") << "\n";
        }
        
        cout << "Total Page Faults: " << pageFaults << "\n";
    }
};

int main() {
    cout << "=== PAGE REPLACEMENT ALGORITHMS ===\n";
    
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int frameSize = 3;
    
    cout << "Page Reference String: ";
    for(int page : pages) {
        cout << page << " ";
    }
    cout << "\nFrame Size: " << frameSize << "\n";
    
    PageReplacement pr(pages, frameSize);
    
    pr.fifo();
    pr.lru();
    pr.optimal();
    
    return 0;
}
