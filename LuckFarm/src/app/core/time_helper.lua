local _M = {};
-- local ffi = require("ffi")
-- ffi.cdef[[
--     struct timeval {
--         long int tv_sec;
--         long int tv_usec;
--     };
--     int gettimeofday(struct timeval *tv, void *tz);
-- ]];
-- local tm = ffi.new("struct timeval");

-- -- 返回微秒级时间戳
-- function _M.current_time_millis()   
--     ffi.C.gettimeofday(tm,nil);
--     local sec =  tonumber(tm.tv_sec);
--     local usec =  tonumber(tm.tv_usec);
--     return sec + usec * 10^-6;
-- end

function _M.current_time_millis()   
    local socket = require "socket"
    local start_time = socket.gettime()
    for i=1,100 do
        local x = 1
    end
    local end_time= socket.gettime()
    local use_time = (end_time - start_time )*1000
    print("start_time:"..start_time..",end_time:"..end_time..",used time: "..use_time .."ms \n")
    return start_time
end

return _M;