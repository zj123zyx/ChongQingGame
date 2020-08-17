
local DataBuilder = {}

function DataBuilder.buildPacket(iType,iBody,str)

    local packet=iType..';'..iBody..";"..str..";;;;\n" 

    return packet
end

--101448;0;0;0;0;8;
--101454;0;0;0;1;8;181123095;

function DataBuilder.buildStream(iType,iBody)

    local packet=iType..";"..iBody.."\n"

    -- local len = strnum_len(string.len(packet))

    local len = string.len(packet)

    local t1,t2 = math.modf(len/256)

    local char1 = string.char(t1)
    local char2 = string.char(t2*256)

    -- print("buildStream",packet)

    packet = char1..char2..packet
    -- packet = len..packet

    -- print("buildStream",packet)

    return packet
end

function DataBuilder.removeChar(input)

    local char1 = string.byte(string.sub(input,1,1))
    local char2 = string.byte(string.sub(input,2,2))

    input = string.sub(input,3,string.len(input))

    -- print("input",input)

    local len = string.len(input)

    local charval = string.sub(input,len, len)

    local pos = string.find(input, '\n')


    while pos~= nil and pos>0 and pos <= string.len(input) do
    
        local preSub = string.sub(input,1, pos-1)

        local nextSub = ""

        if pos+1 > string.len(input) then
            nextSub = ""
        else
            nextSub = string.sub(input,pos+1, string.len(input))
        end

        input = preSub..nextSub
        pos = string.find(input, '\n')
    end
    
    return input

end

function DataBuilder.removeEndChar(input)
    
    local len = string.len(input)

    local charval = string.sub(input,len, len)

    while charval ~= ";" do
        len = len-1
        charval = string.sub(input,len, len)
    end

    local data = string.sub(input,1, len)
    
    return data

end

function DataBuilder.getHeadEndPos(input)
    

    local pos = 0
    local cnt = 0

    for st,sp in function() return string.find(input, ';', pos, true) end do
        pos = sp + 1
        cnt = cnt + 1

        if cnt >= 6 then
            break
        end
    end

    return pos

end

function DataBuilder.getPreData(data,dataarray)
    local head=string.sub(data,1, string.find(data, dataarray[6])-1)
    return head
end

function DataBuilder.subPacketHead(data,dataarray)
    local head=string.sub(data,1, string.find(data, dataarray[6])-1)
    return head
end

-- function DataBuilder.getPacketBody(data)


--     -- if data and string.len(data) >= DataBuilder.SOCKET_HEADER_LENGTH then 
--     if data then 
        
--         local dataarray = string.split(data, ';')

--         if #dataarray >= 6 then

--             local oneMsgLen = tonumber(string.sub(dataarray[1],1,6))
--             local iType = string.sub(dataarray[1],7,12)

--             -- local headPos = DataBuilder.getHeadEndPos(data)

--             -- print("headPos",headPos)

--             -- local headData = string.sub(data,1,headPos-1)
--             -- local bodyData = string.sub(data,headPos,string.len(data))


--             -- local iType = tonumber(dataarray[1]) 

--             -- local bodylen = tonumber(dataarray[2])
--             -- local bodylen = string.len(bodyData)

--             -- local headlen = string.len(headData)

--             local messagelen = string.len(data)

--             local onebody = string.sub(data,7,oneMsgLen)

--             print("iType-----",iType, onebody,oneMsgLen,messagelen)

--             if messagelen >= oneMsgLen then 

--                 -- print("---------bodydata-----1", onebody)

--                 -- print("---------bodydata-----2", string.sub(data,bodylen+headlen+1,messagelen))

--                 return iType, onebody, string.sub(data,oneMsgLen+6,messagelen)
--             else
--                 return type, nil, data
--             end

--         end
--     else
--         if data then print("Socket Data Pack Len :",string.len(data)) end
--     end

--     return nil, nil, nil
-- end

function DataBuilder.getPacketBody(data)


    -- if data and string.len(data) >= DataBuilder.SOCKET_HEADER_LENGTH then 
    if data then 
        
        local dataarray = string.split(data, ';')

        if #dataarray >= 6 then


            local headPos = DataBuilder.getHeadEndPos(data)

            -- print("headPos",headPos)

            local headData = string.sub(data,1,headPos-1)
            local bodyData = string.sub(data,headPos,string.len(data))


            local iType = tonumber(dataarray[1]) 

            -- local bodylen = tonumber(dataarray[2])
            local bodylen = string.len(bodyData)

            local headlen = string.len(headData)

            local messagelen = string.len(data)

            local onebody = string.sub(data,1,bodylen+headlen)

            -- print("iType-----",iType, bodylen+headlen,messagelen)

            if messagelen >= bodylen+headlen then 

                -- print("---------bodydata-----1", onebody)

                -- print("---------bodydata-----2", string.sub(data,bodylen+headlen+1,messagelen))

                return iType, onebody, string.sub(data,bodylen+headlen+1,messagelen)
            else
                return type, nil, data
            end

        end
    else
        if data then print("Socket Data Pack Len :",string.len(data)) end
    end

    return nil, nil, nil
end

return DataBuilder