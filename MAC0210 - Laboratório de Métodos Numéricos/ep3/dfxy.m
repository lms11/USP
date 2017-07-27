function value = dfxy(f, val_i, val_j, lim_x, lim_y, hx, hy)
    delX = dfx(f, val_i, lim_x, hx);
    delXY = dfy(delX, val_j, lim_y, hy);
    value = delXY(val_i, val_j);
endfunction
