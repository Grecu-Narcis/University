import React from "react"
import { PagingContextProps } from "./PagingContextProps.types"

export type PagingContextProviderType = {
    pagingContext: PagingContextProps,
    children: React.ReactNode;
}