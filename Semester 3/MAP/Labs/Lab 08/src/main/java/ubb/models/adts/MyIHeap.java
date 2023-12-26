package ubb.models.adts;

import ubb.models.values.IValue;

import java.util.Map;

public interface MyIHeap {
    int getCurrentAddress();
    int allocate(IValue valueToAllocate);
    Map<Integer, IValue> getContent();
    IValue getValueAtAddress(int addressToLook);
    void updateAddress(Integer addressToUpdate, IValue newValue);
    boolean isDefined(Integer addressToLook);
    void setContent(Map<Integer, IValue> newHeapValues);
}
