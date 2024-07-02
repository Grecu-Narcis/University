import { createContext } from 'react';
import { PagingContextProps } from '../types/PagingContextProps.types';
import { PagingContextProviderType } from '../types/PagingContextProviderType.types';

export const PagingContext = createContext<PagingContextProps | null>(null);

function PagingContextProvider({ pagingContext, children }: PagingContextProviderType) {
    return <PagingContext.Provider value={pagingContext}>{children}</PagingContext.Provider>;
}

export { PagingContextProvider };
